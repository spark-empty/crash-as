/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2017  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * This is copied from [tinyos](https://github.com/ddk50/tinyos) pci-main
 */
#ifndef _PCI_CORE_H_
#define _PCI_CORE_H_
/* ============================ [ INCLUDES  ] ====================================================== */
#include "Std_Types.h"

/* ============================ [ MACROS    ] ====================================================== */
/*
 * Under PCI, each device has 256 bytes of configuration address space,
 * of which the first 64 bytes are standardized as follows:
 */
#define PCI_STD_HEADER_SIZEOF	64
#define PCI_VENDOR_ID		0x00	/* 16 bits */
#define PCI_DEVICE_ID		0x02	/* 16 bits */
#define PCI_COMMAND		0x04	/* 16 bits */
#define  PCI_COMMAND_IO		0x1	/* Enable response in I/O space */
#define  PCI_COMMAND_MEMORY	0x2	/* Enable response in Memory space */
#define  PCI_COMMAND_MASTER	0x4	/* Enable bus mastering */
#define  PCI_COMMAND_SPECIAL	0x8	/* Enable response to special cycles */
#define  PCI_COMMAND_INVALIDATE	0x10	/* Use memory write and invalidate */
#define  PCI_COMMAND_VGA_PALETTE 0x20	/* Enable palette snooping */
#define  PCI_COMMAND_PARITY	0x40	/* Enable parity checking */
#define  PCI_COMMAND_WAIT	0x80	/* Enable address/data stepping */
#define  PCI_COMMAND_SERR	0x100	/* Enable SERR */
#define  PCI_COMMAND_FAST_BACK	0x200	/* Enable back-to-back writes */
#define  PCI_COMMAND_INTX_DISABLE 0x400 /* INTx Emulation Disable */

#define PCI_CLASS_REVISION	0x08	/* High 24 bits are class, low 8 revision */
#define PCI_REVISION_ID		0x08	/* Revision ID */
#define PCI_CLASS_PROG		0x09	/* Reg. Level Programming Interface */
#define PCI_CLASS_DEVICE	0x0a	/* Device class */
/*
 * Base addresses specify locations in memory or I/O space.
 * Decoded size can be determined by writing a value of
 * 0xffffffff to the register, and reading it back.  Only
 * 1 bits are decoded.
 */
#define PCI_BASE_ADDRESS_0	0x10	/* 32 bits */
#define PCI_BASE_ADDRESS_1	0x14	/* 32 bits [htype 0,1 only] */
#define PCI_BASE_ADDRESS_2	0x18	/* 32 bits [htype 0 only] */
#define PCI_BASE_ADDRESS_3	0x1c	/* 32 bits */
#define PCI_BASE_ADDRESS_4	0x20	/* 32 bits */
#define PCI_BASE_ADDRESS_5	0x24	/* 32 bits */

/* 0x35-0x3b are reserved */
#define PCI_INTERRUPT_LINE	0x3c	/* 8 bits */
#define PCI_INTERRUPT_PIN	0x3d	/* 8 bits */
#define PCI_MIN_GNT		0x3e	/* 8 bits */
#define PCI_MAX_LAT		0x3f	/* 8 bits */

/* PCI bus */

#define PCI_DEVFN(slot, func)   ((((slot) & 0x1f) << 3) | ((func) & 0x07))
#define PCI_BUS_NUM(x)          (((x) >> 8) & 0xff)
#define PCI_SLOT(devfn)         (((devfn) >> 3) & 0x1f)
#define PCI_FUNC(devfn)         ((devfn) & 0x07)
#define PCI_BUILD_BDF(bus, devfn)     ((bus << 8) | (devfn))
#define PCI_BUS_MAX             256
#define PCI_DEVFN_MAX           256
#define PCI_SLOT_MAX            32
#define PCI_FUNC_MAX            8

#define     PCI_DEVICE(vid, did, name)                              \
	{PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), 0xff, mmiocfg_##vid##_##did}

#define     PCI_BRIDGE(vid, did, name, bridge)                          \
	{PCI_VENDOR_ID_##vid, PCI_DEVICE_ID_##did, (name), (bridge), NULL}

/* linux compatible version API */
#define pci_bus_read_config_byte(pdev,offset)     pci_read_config_reg8(&(pdev->dev),offset)
#define pci_bus_read_config_word(pdev,offset)     pci_read_config_reg16(&(pdev->dev),offset)
#define pci_bus_read_config_dword(pdev,offset)    pci_read_config_reg32(&(pdev->dev),offset)
#define pci_bus_write_config_byte(pdev,offset,v)  pci_write_config_reg8(&(pdev->dev),offset,v)
#define pci_bus_write_config_word(pdev,offset,v)  pci_write_config_reg16(&(pdev->dev),offset,v)
#define pci_bus_write_config_dword(pdev,offset,v) pci_write_config_reg32(&(pdev->dev),offset,v)
/* ============================ [ TYPES     ] ====================================================== */
typedef struct
{
	uint32					mem_addr[6];
	uint32					mem_size[6];
	uint16					io_addr[6];
	uint16					io_size[6];
} pci_mmio_cfg;
typedef struct __pci_vendor_info {
	uint16			vendor_id;			/* vendor id */
	uint16			device_id;			/* device id */
	const char		*name;			/* device name */
	uint8			bridge_type;	/* bridge type or 0xff */
	const pci_mmio_cfg* mmio_cfg;
} pci_vendor_info;

typedef struct __pci_device_info {
	pci_vendor_info		info;
	uint32				base_addr;
	uint8				base_class;
	uint8				sub_class;
} pci_device_info;

typedef struct __pci_res {
	uint8		bus;		/* バス番号 */
	uint8		dev;		/* デバイス番号 */
	uint8		fn;			/* 機能番号 */
} pci_reg;

typedef struct __pci_dev {
	int						pci_num;
	struct __pci_dev		*next;
	uint32					mem_addr[6];
	uint32					mem_size[6];
	uint16					io_addr[6];
	uint16					io_size[6];
	uint8					irq_num;
	uint8					intr_num;
	uint16					vendor_id;
	uint16					device_id;
	uint16					subsys_id;
	const pci_vendor_info			*vendor;
	pci_reg					dev;
	void*					priv;
} pci_dev;


#include "pci_cfg.h"
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
/* ============================ [ FUNCTIONS ] ====================================================== */
int pci_generic_config_write(unsigned int busnr, unsigned int devfn,
							 int where, int size, u32 val);
int pci_generic_config_read(unsigned int busnr, unsigned int devfn,
							int where, int size, u32 *val);

uint8 pci_read_config_reg8(pci_reg*, uint8);
uint16 pci_read_config_reg16(pci_reg*, uint8);
uint32 pci_read_config_reg32(pci_reg*, uint8);

void pci_write_config_reg8(pci_reg*, uint8, const uint8);
void pci_write_config_reg16(pci_reg*, uint8, const uint16);
void pci_write_config_reg32(pci_reg*, uint8, const uint32);

void disable_pci_resource(pci_dev*);
void enable_pci_resource(pci_dev*);

void enable_pci_interrupt(pci_dev*);
void disable_pci_interrupt(pci_dev*);

int pci_register_irq(uint32 irq_num, void (*handler)());
int pci_unregister_irq(uint32 irq_num);

pci_dev *find_pci_dev_from_reg(pci_reg *reg);
pci_dev *find_pci_dev_from_id(uint32 vendor_id, uint32 device_id);

void pci_search_all_device(void);

void* pci_get_memio(pci_dev *pdev, int index);
#endif /* _PCI_CORE_H_ */
