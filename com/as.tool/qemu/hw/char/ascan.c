/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/pci/pci.h"
#include "qemu/event_notifier.h"
#include <time.h>
#include <sys/queue.h>
#include <pthread.h>
/* ============================ [ MACROS    ] ====================================================== */
#define TYPE_PCI_ASCAN_DEV "pci-ascan"
#define PCI_ASCAN_DEV(obj)     OBJECT_CHECK(PCIASCANDevState, (obj), TYPE_PCI_ASCAN_DEV)
/* sizes must be power of 2 in PCI */
#define ASCAN_IO_SIZE 1<<4
#define ASCAN_MMIO_SIZE 1<<6

enum {
	FLG_RX = 0x01,
	FLG_TX = 0x02,
};

enum{
	REG_BUS_NAME  = 0x00,
	REG_BUSID     = 0x04,
	REG_PORT      = 0x08,
	REG_CANID     = 0x0C,
	REG_CANDLC    = 0x10,
	REG_CANDATA   = 0x14,
	REG_CANSTATUS = 0x18,
	REG_CMD       = 0x1C,
};

/* ============================ [ TYPES     ] ====================================================== */
struct Can_Bus_s {
	uint32_t busid;

	uint32_t canid;
	uint32_t candlc;
	uint32_t rwpos;
	uint8_t  data[64];
	STAILQ_ENTRY(Can_Bus_s) entry;	/* entry for Can_PduQueue_s, sort by CANID queue*/
};
typedef struct PCIASCANDevState {
	PCIDevice parent_obj;

	/* for PIO */
	MemoryRegion io;
	/* for MMIO */
	MemoryRegion mmio;
	/* irq used */
	qemu_irq irq;
	/* dma buf size */
	unsigned int dma_size;
	/* buffer copied with the dma operation on RAM */
	char *dma_buf;
	/* did we throw an interrupt ? */
	int threw_irq;
	/* id of the device, writable */
	int id;

	STAILQ_HEAD(,Can_Bus_s) head;

	struct Can_Bus_s* curbus;	/* current bus for reading data */

	char bus_name[64];
	uint32_t bn_pos;

	uint32_t flag;

	uint32_t busid;
	uint32_t port;
} PCIASCANDevState;

static Property ascan_properties[] = {

DEFINE_PROP_END_OF_LIST(), };
/* ============================ [ DECLARES  ] ====================================================== */
extern void luai_canlib_open(void);
extern void luai_canlib_close(void);
extern int can_open(unsigned long busid,const char* device_name,unsigned long port, unsigned long baudrate);
extern int can_write(unsigned long busid,unsigned long canid,unsigned long dlc,unsigned char* data);
extern int can_read(unsigned long busid,unsigned long canid,unsigned long* p_canid,unsigned long *dlc,unsigned char* data);

static uint64_t ascan_mmioread(void *opaque, hwaddr addr, unsigned size);
static void ascan_mmiowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size);
static uint64_t ascan_ioread(void *opaque, hwaddr addr, unsigned size);
static void ascan_iowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size);
static void pci_ascandev_class_init(ObjectClass *klass, void *data);
/* ============================ [ DATAS     ] ====================================================== */
/*
 * Callbacks called when the Memory Region
 * representing the MMIO space is
 * accessed.
 */
static const MemoryRegionOps ascan_mmio_ops = {
	.read = ascan_mmioread,
	.write = ascan_mmiowrite,
	.endianness = DEVICE_NATIVE_ENDIAN,
	.valid = {
		.min_access_size = 4,
		.max_access_size = 4,
	},
};

/*
 * Callbacks called when the Memory Region
 * representing the PIO space is
 * accessed.
 */
static const MemoryRegionOps ascan_io_ops = {
	.read = ascan_ioread,
	.write = ascan_iowrite,
	.endianness = DEVICE_NATIVE_ENDIAN,
	.valid = {
		.min_access_size = 4,
		.max_access_size = 4,
	},
};

/* Contains all the informations of the device
 * we are creating.
 * class_init will be called when we are defining
 * our device.
 */
static const TypeInfo pci_ascan_info = {
	.name = TYPE_PCI_ASCAN_DEV,
	.parent = TYPE_PCI_DEVICE,
	.instance_size = sizeof(PCIASCANDevState),
	.class_init = pci_ascandev_class_init,
#ifdef INTERFACE_CONVENTIONAL_PCI_DEVICE
	.interfaces = (InterfaceInfo[]) {
		{ INTERFACE_CONVENTIONAL_PCI_DEVICE },
		{},
	},
#endif
};

/* ============================ [ LOCALS    ] ====================================================== */
static struct Can_Bus_s* getBus(PCIASCANDevState *d, uint32_t busid)
{
	struct Can_Bus_s* b;

	STAILQ_FOREACH(b, &d->head, entry)
	{
		if(b->busid == busid)
		{
			break;
		}
	}

	return b;
}

static void checkBus(PCIASCANDevState *d)
{
	struct Can_Bus_s* b;

	STAILQ_FOREACH(b, &d->head, entry)
	{
		if(d->flag&(FLG_RX<<(4*b->busid)))
		{
			/* already has message ready for read */
		}
		else
		{
			int rv;
			rv = can_read(b->busid, -1, (unsigned long*)&b->canid, (unsigned long*)&b->candlc, b->data);

			if(TRUE == rv)
			{
				d->flag |= FLG_RX<<(4*b->busid);
			}
		}
	}
}

static void ascan_iowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size) {
	int i;
	PCIASCANDevState *d = (PCIASCANDevState *) opaque;
	PCIDevice *pci_dev = (PCIDevice *) opaque;

	switch (addr) {
	case 0:
		if (value) {
			/* throw an interrupt */
			d->threw_irq = 1;
			pci_irq_assert(pci_dev);

		} else {
			/*  ack interrupt */
			pci_irq_deassert(pci_dev);
			d->threw_irq = 0;
		}
		break;
	case 4:
		/* throw a random DMA */
		for (i = 0; i < d->dma_size; ++i)
			d->dma_buf[i] = rand();
		cpu_physical_memory_write(value, (void *) d->dma_buf, d->dma_size);
		break;
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
	}

}

static uint64_t ascan_ioread(void *opaque, hwaddr addr, unsigned size) {
	PCIASCANDevState *d = (PCIASCANDevState *) opaque;

	switch (addr) {
	case 0:
		/* irq status */
		return d->threw_irq;
		break;
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
		return 0x0;
	}
}

static uint64_t ascan_mmioread(void *opaque, hwaddr addr, unsigned size) {
	PCIASCANDevState *d = (PCIASCANDevState *) opaque;
	PCIDevice *pci_dev = (PCIDevice *) opaque;
	uint64_t rv;
	switch (addr) {
	case REG_CANSTATUS:
		pci_irq_deassert(pci_dev);
		checkBus(d);
		rv = d->flag;
		d->flag = 0;
		return rv;
	break;
	case REG_CANID:
		assert(d->curbus);
		return d->curbus->canid;
	break;
	case REG_CANDLC:
		assert(d->curbus);
		/* read DLC and then read data */
		d->curbus->rwpos = 0;
		return d->curbus->candlc;
	break;
	case REG_CANDATA:
		assert(d->curbus);
		assert(d->curbus->rwpos<sizeof(d->curbus->data));
		return d->curbus->data[d->curbus->rwpos++];
	break;
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
		return 0x0;

	}
}

static void ascan_mmiowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size) {
	PCIASCANDevState *d = (PCIASCANDevState *) opaque;
	PCIDevice *pci_dev = (PCIDevice *) opaque;
	switch (addr) {
	case REG_BUS_NAME:
		/* change the id */
		if(d->bn_pos < (sizeof(d->bus_name)-1))
		{
			d->bus_name[d->bn_pos] = value;
			d->bn_pos++;
		}
		break;
	case REG_BUSID:
		d->busid = value;
		assert(value < 8);
		d->curbus = getBus(d, d->busid);
		break;
	case REG_PORT:
		d->port = value;
		break;
	case REG_CANID:
		assert(d->curbus);
		d->curbus->canid = value;
	break;
	case REG_CANDLC:
		assert(d->curbus);
		d->curbus->candlc = value;
		d->curbus->rwpos = 0;
	break;
	case REG_CANDATA:
		assert(d->curbus);
		assert(d->curbus->rwpos < sizeof(d->curbus->data));
		d->curbus->data[d->curbus->rwpos++] = value;
	break;
	case REG_CMD:
		switch(value)
		{
			case 0:
				d->bn_pos = 0; /* do this command first before config bus name */
				memset(d->bus_name, 0, sizeof(d->bus_name));
			break;
			case 1:
			{
				int rv = can_open(d->busid, d->bus_name, d->port, 1000000);
				if(TRUE == rv)
				{
					struct Can_Bus_s *p = malloc(sizeof(struct Can_Bus_s));
					assert(p);
					p->busid = d->busid;
					STAILQ_INSERT_TAIL(&d->head, p, entry);
					printf("start %s busid(%d) port(%d) okay\n", d->bus_name, d->busid,  d->port);
				}
				else
				{
					printf("please start up %s for simulation:\n"
							"\tsudo modprobe vcan\n"
							"\tsudo ip link add dev can%d type vcan\n"
							"\tsudo ip link set up can%d\n",
							(0==strcmp(d->bus_name,"socket"))?"vcan":d->bus_name,
									d->port,d->port);
				}
			}
			break;
			case 2:
			{
				int rv;
				assert(d->curbus);
				rv = can_write(d->busid,d->curbus->canid,d->curbus->candlc,d->curbus->data);
				if(TRUE == rv)
				{
					d->flag |= FLG_TX<<(4*d->busid);
					pci_irq_assert(pci_dev);
				}
			}
			break;
			default:
				printf ("%s: Bad command 0x%x\n", __func__, (int)value);
			break;
		}
	break;
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);

	}
}

/* Callbacks for MMIO and PIO regions are registered here */
static void ascan_io_setup(PCIASCANDevState *d) {
	memory_region_init_io(&d->mmio, OBJECT(d), &ascan_mmio_ops, d, "ascan_mmio",
			ASCAN_MMIO_SIZE);
	memory_region_init_io(&d->io, OBJECT(d), &ascan_io_ops, d, "ascan_io",
			ASCAN_IO_SIZE);
}

/* When device is loaded */
static int pci_ascandev_init(PCIDevice *pci_dev) {
	/* init the internal state of the device */
	PCIASCANDevState *d = PCI_ASCAN_DEV(pci_dev);
	d->dma_size = 0x1ffff * sizeof(char);
	d->dma_buf = malloc(d->dma_size);
	d->id = 0xcaac;
	d->threw_irq = 0;
	d->flag = 0;
	uint8_t *pci_conf;

	STAILQ_INIT(&d->head);
	/* create the memory region representing the MMIO and PIO
	 * of the device
	 */
	ascan_io_setup(d);
	/*
	 * See linux device driver (Edition 3) for the definition of a bar
	 * in the PCI bus.
	 */
	pci_register_bar(pci_dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &d->io);
	pci_register_bar(pci_dev, 1, PCI_BASE_ADDRESS_SPACE_MEMORY, &d->mmio);

	pci_conf = pci_dev->config;
	/* also in ldd, a pci device has 4 pin for interrupt
	 * here we use pin B.
	 */
	pci_conf[PCI_INTERRUPT_PIN] = 0x02;

	return 0;
}

/* When device is unloaded
 * Can be useful for hot(un)plugging
 */
static void pci_ascandev_uninit(PCIDevice *dev) {
	PCIASCANDevState *d = (PCIASCANDevState *) dev;
	free(d->dma_buf);
}

static void qdev_pci_ascandev_reset(DeviceState *dev) {
	PCIASCANDevState *d = (PCIASCANDevState *) dev;
	while(FALSE == STAILQ_EMPTY(&d->head))
	{
		struct Can_Bus_s *p = STAILQ_FIRST(&d->head);
		STAILQ_REMOVE_HEAD(&d->head,entry);

		free(p);
	}
	luai_canlib_close();
	luai_canlib_open();
}

/* Called when the device is defined
 * PCI configuration is defined here
 * We inherit from PCIDeviceClass
 * Also see ldd for the meaning of the different args
 */
static void pci_ascandev_class_init(ObjectClass *klass, void *data) {
	DeviceClass *dc = DEVICE_CLASS(klass);
	PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);
	k->init = pci_ascandev_init;
	k->exit = pci_ascandev_uninit;
	/* this identify our device */
	k->vendor_id = 0xcaac;
	k->device_id = 0x0001;
	k->class_id = PCI_CLASS_OTHERS;
	set_bit(DEVICE_CATEGORY_MISC, dc->categories);

	k->revision = 0x00;
	dc->desc = "PCI ASCAN";
	/* qemu user things */
	dc->props = ascan_properties;
	dc->reset = qdev_pci_ascandev_reset;
}

/* function called before the qemu main
 * it will define our device
 */
static void pci_ascan_register_types(void) {
	type_register_static(&pci_ascan_info);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
/* macro actually defining our device and registering it in qemu*/
type_init(pci_ascan_register_types);
