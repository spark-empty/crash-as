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
#ifndef __TAPTEST__
#include "qemu/osdep.h"
#include "hw/hw.h"
#include "hw/pci/pci.h"
#include "qemu/event_notifier.h"
#endif /* __TAPTEST__ */
#include <stdint.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#ifdef _WIN32
#include "pcap.h"
#else
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <sys/poll.h>
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define TYPE_PCI_ASNET_DEV "pci-asnet"
#define PCI_ASNET_DEV(obj)     OBJECT_CHECK(PCIASNETDevState, (obj), TYPE_PCI_ASNET_DEV)
/* sizes must be power of 2 in PCI */
#define ASNET_IO_SIZE 1<<4
#define ASNET_MMIO_SIZE 1<<6

#define IFCONFIG_BIN "ifconfig "

#define DEVTAP "/dev/net/tun"
#define IFCONFIG_ARGS "%s inet %d.%d.%d.%d netmask %d.%d.%d.%d"

#define ETHARP_HWADDR_LEN 6
#define ADAPTER_NAME_LEN       128
#define ADAPTER_DESC_LEN       128

/* For compatibility with old pcap */
#define PCAP_OPENFLAG_PROMISCUOUS     1

#define LWIP_MAX(x , y)  (((x) > (y)) ? (x) : (y))
#define LWIP_MIN(x , y)  (((x) < (y)) ? (x) : (y))

/* Get one byte from the 4-byte address */
#define ip4_addr1(ipaddr) (((uint8_t*)(ipaddr))[0])
#define ip4_addr2(ipaddr) (((uint8_t*)(ipaddr))[1])
#define ip4_addr3(ipaddr) (((uint8_t*)(ipaddr))[2])
#define ip4_addr4(ipaddr) (((uint8_t*)(ipaddr))[3])

enum {
	FLG_RX = 0x01,
	FLG_TX = 0x02,
};

enum{
	REG_MACL      = 0x00,
	REG_MACH      = 0x04,
	REG_MTU       = 0x08,
	REG_DATA      = 0x0C,
	REG_LENGTH    = 0x10,
	REG_NETSTATUS = 0x14,
	REG_GW        = 0x18,
	REG_NETMASK   = 0x1C,
	REG_CMD       = 0x20,
#ifdef _WIN32
	REG_ADAPTERID = 0x24,
#endif
};
/* ============================ [ TYPES     ] ====================================================== */
#ifdef _WIN32
struct eth_addr {
	uint8_t addr[ETHARP_HWADDR_LEN];
} __attribute__((packed));
/* Packet Adapter informations */
struct pcapif_private {
	void            *input_fn_arg;
	pcap_t          *adapter;
	char             name[ADAPTER_NAME_LEN];
	char             description[ADAPTER_DESC_LEN];
	int              shutdown_called;
};
#endif
typedef struct PCIASNETDevState {
#ifndef __TAPTEST__
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
#endif

	int fd;

	/** maximum transfer unit (in bytes) */
	uint32_t mtu;
	uint8_t hwaddr_len;
	uint8_t hwaddr[ETHARP_HWADDR_LEN];
	uint32_t gw;
	uint32_t netmask;

	int rxlength;
	uint32_t rxpos;
	uint8_t rxdata[2048];

	uint32_t txlength;
	uint32_t txpos;
	uint8_t txdata[2048];

	uint32_t flag;

#ifdef _WIN32
	struct pcapif_private *pcap;
	int adapter_num;
#endif
} PCIASNETDevState;
#ifndef __TAPTEST__
static Property asnet_properties[] = {

DEFINE_PROP_END_OF_LIST(), };
#endif
/* ============================ [ DECLARES  ] ====================================================== */
#ifndef __TAPTEST__
static uint64_t asnet_mmioread(void *opaque, hwaddr addr, unsigned size);
static void asnet_mmiowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size);
static uint64_t asnet_ioread(void *opaque, hwaddr addr, unsigned size);
static void asnet_iowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size);
static void pci_asnetdev_class_init(ObjectClass *klass, void *data);
#endif
/* ============================ [ DATAS     ] ====================================================== */
#ifndef __TAPTEST__
/*
 * Callbacks called when the Memory Region
 * representing the MMIO space is
 * accessed.
 */
static const MemoryRegionOps asnet_mmio_ops = {
	.read = asnet_mmioread,
	.write = asnet_mmiowrite,
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
static const MemoryRegionOps asnet_io_ops = {
	.read = asnet_ioread,
	.write = asnet_iowrite,
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
static const TypeInfo pci_asnet_info = {
	.name = TYPE_PCI_ASNET_DEV,
	.parent = TYPE_PCI_DEVICE,
	.instance_size = sizeof(PCIASNETDevState),
	.class_init = pci_asnetdev_class_init,
#ifdef INTERFACE_CONVENTIONAL_PCI_DEVICE
	.interfaces = (InterfaceInfo[]) {
		{ INTERFACE_CONVENTIONAL_PCI_DEVICE },
		{},
	},
#endif
};
#endif /* __TAPTEST__ */
/* ============================ [ LOCALS    ] ====================================================== */
#ifdef __TAPTEST__
void asmem(const char* prefix, const void* address,size_t size)
{
	uint32_t i,j;
	uint8_t *src;
	src = (uint8_t*)address;
	if(8 == sizeof(unsigned long))
	{
		printf("%16s :: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n",prefix);
	}
	else
	{
		printf("%8s :: 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n",prefix);
	}

	for(i=0; i<(size+15)/16; i++)
	{
		unsigned long a = (unsigned long)src+i*16;
		if( 8 == sizeof(unsigned long))
		{
			printf("%08X%08X ::",(uint32_t)(a>>32),(uint32_t)a);
		}
		else
		{
			printf("%08X ::",(uint32_t)a);
		}

		fflush(stdout);

		for(j=0;j<16;j++)
		{
			if((i*16+j)<size)
			{
				printf(" %02X",src[i*16+j]);
			}
			else
			{
				printf("   ");
			}
		}
		printf("\t");
		for(j=0;j<16;j++)
		{
			if(((i*16+j)<size) && isprint(src[i*16+j]))
			{
				printf("%c",src[i*16+j]);
			}
			else
			{
				printf(".");
			}
		}
		printf("\n");
	}

    fflush(stdout);

}

#endif
#ifdef _WIN32
/**
 * Open a network adapter and set it up for packet input
 *
 * @param adapter_num the index of the adapter to use
 * @param arg argument to pass to input
 * @return an adapter handle on success, NULL on failure
 */
static struct pcapif_private*
pcapif_init_adapter(int adapter_num, void *arg)
{
  int i;
  int number_of_adapters;
  struct pcapif_private *pa;
  char errbuf[PCAP_ERRBUF_SIZE+1];

  pcap_if_t *alldevs;
  pcap_if_t *d;
  pcap_if_t *used_adapter = NULL;

  pa = (struct pcapif_private *)malloc(sizeof(struct pcapif_private));
  if (!pa) {
    printf("Unable to alloc the adapter!\n");
    return NULL;
  }

  memset(pa, 0, sizeof(struct pcapif_private));
  pa->input_fn_arg = arg;

  /* Retrieve the interfaces list */
  if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    free(pa);
    return NULL; /* no adapters found */
  }
  /* get number of adatpers and adapter pointer */
  for (d = alldevs, number_of_adapters = 0; d != NULL; d = d->next, number_of_adapters++) {
    if (number_of_adapters == adapter_num) {
      char *desc = d->description;
      size_t len;

      len = strlen(d->name);
      assert(len < ADAPTER_NAME_LEN);
      strcpy(pa->name, d->name);

      used_adapter = d;
      /* format vendor description */
      if (desc != NULL) {
        len = strlen(desc);
        if (strstr(desc, " ' on local host") != NULL) {
          len -= 16;
        }
        else if (strstr(desc, "' on local host") != NULL) {
          len -= 15;
        }
        if (strstr(desc, "Network adapter '") == desc) {
          len -= 17;
          desc += 17;
        }
        len = LWIP_MIN(len, ADAPTER_DESC_LEN-1);
        while ((desc[len-1] == ' ') || (desc[len-1] == '\t')) {
          /* don't copy trailing whitespace */
          len--;
        }
        strncpy(pa->description, desc, len);
        pa->description[len] = 0;
      } else {
        strcpy(pa->description, "<no_desc>");
      }
    }
  }

#ifndef PCAPIF_LIB_QUIET
  /* Scan the list printing every entry */
  for (d = alldevs, i = 0; d != NULL; d = d->next, i++) {
    char *desc = d->description;
    char descBuf[128];
    size_t len;
    const char* devname = d->name;
    if (d->name == NULL) {
      devname = "<unnamed>";
    } else {
      if (strstr(devname, "\\Device\\") == devname) {
        /* windows: strip the first part */
        devname += 8;
      }
    }
    printf("%2i: %s\n", i, devname);
    if (desc != NULL) {
      /* format vendor description */
      len = strlen(desc);
      if (strstr(desc, " ' on local host") != NULL) {
        len -= 16;
      }
      else if (strstr(desc, "' on local host") != NULL) {
        len -= 15;
      }
      if (strstr(desc, "Network adapter '") == desc) {
        len -= 17;
        desc += 17;
      }
      len = LWIP_MIN(len, 127);
      while ((desc[len-1] == ' ') || (desc[len-1] == '\t')) {
        /* don't copy trailing whitespace */
        len--;
      }
      strncpy(descBuf, desc, len);
      descBuf[len] = 0;
      printf("     Desc: \"%s\"\n", descBuf);
    }
  }
#endif /* PCAPIF_LIB_QUIET */

  /* invalid adapter index -> check this after printing the adapters */
  if (adapter_num < 0) {
    printf("Invalid adapter_num: %d\n", adapter_num);
    free(pa);
    pcap_freealldevs(alldevs);
    return NULL;
  }
  /* adapter index out of range */
  if (adapter_num >= number_of_adapters) {
    printf("Invalid adapter_num: %d\n", adapter_num);
    free(pa);
    pcap_freealldevs(alldevs);
    return NULL;
  }
#ifndef PCAPIF_LIB_QUIET
  printf("Using adapter_num: %d\n", adapter_num);
#endif /* PCAPIF_LIB_QUIET */
  /* set up the selected adapter */

  assert( used_adapter != NULL);

  /* Open the device */
  pa->adapter = pcap_open_live(used_adapter->name,/* name of the device */
                               65536,             /* portion of the packet to capture */
                                                  /* 65536 guarantees that the whole packet will be captured on all the link layers */
                               PCAP_OPENFLAG_PROMISCUOUS,/* promiscuous mode */
                               -1,                 /* wait 0 ms in ethernetif_poll */
                               errbuf);           /* error buffer */
  if (pa->adapter == NULL) {
    printf("\nUnable to open the adapter. %s is not supported by WinPcap\n", d->name);
    /* Free the device list */
    pcap_freealldevs(alldevs);
    free(pa);
    return NULL;
  }
  printf("Using adapter: \"%s\"\n", pa->description);
  pcap_freealldevs(alldevs);

  return pa;
}
static int low_level_probe(PCIASNETDevState *d,const char *name)
{
	int adapter_num = d->adapter_num;
	struct pcapif_private *pa;

	/* Do whatever else is needed to initialize interface. */
	pa = pcapif_init_adapter(adapter_num, NULL);
	if (pa == NULL) {
		printf("ERROR initializing network adapter %d!\n", adapter_num);
		return -1;
	}

	d->mtu = 1500;
	d->pcap = pa;

	return 0;
}
static int low_level_output(PCIASNETDevState *d)
{
	struct pcapif_private *pa = d->pcap;
	assert(pa);
	/* signal that packet should be sent */
	if (pcap_sendpacket(pa->adapter, d->txdata, d->txlength) < 0) {
		return -1;
	}
	return 0;
}

/** low_level_input(): Allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 */
static void pcapif_low_level_input(PCIASNETDevState *d, const void *packet, int packet_len)
{
  struct eth_addr *dest = (struct eth_addr*)packet;
  struct eth_addr *src = dest + 1;
  const uint8_t bcast[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const uint8_t ipv4mcast[] = {0x01, 0x00, 0x5e};
  const uint8_t ipv6mcast[] = {0x33, 0x33};

  d->rxlength = 0;
  /* Don't let feedback packets through (limitation in winpcap?) */
  if(!memcmp(src, d->hwaddr, ETHARP_HWADDR_LEN)) {
    /* don't update counters here! */
    return;
  }

  if (memcmp(dest, &d->hwaddr, ETHARP_HWADDR_LEN) &&
    (memcmp(dest, ipv4mcast, 3) || ((dest->addr[3] & 0x80) != 0)) &&
    memcmp(dest, ipv6mcast, 2) &&
    memcmp(dest, bcast, 6)) {
    /* don't update counters here! */
    return;
  }

  d->rxlength = packet_len;
  memcpy(d->rxdata, packet, packet_len);
}

/** pcapif_input: This function is called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that should
 * handle the actual reception of bytes from the network interface.
 */
static void
pcapif_input(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *packet)
{
	int packet_len = pkt_header->caplen;

	/* move received packet into a new pbuf */
	pcapif_low_level_input(user, packet, packet_len);
}

static int low_level_input(PCIASNETDevState *d)
{
	int rv;
	struct pcapif_private *pa = d->pcap;
	assert(pa);

	rv = pcap_dispatch(pa->adapter, 1, pcapif_input, (u_char*)d);

	if(0 == rv)
	{
		return -1;
	}
	else if(rv < 0)
	{
		printf("asnet rx error: %s\n", pcap_geterr(pa->adapter));
	}
	else
	{
		if(d->rxlength > 0)
		{
			return 0;
		}
	}

	return -1;
}
#else  /* _WIN32 */
static int low_level_probe(PCIASNETDevState *d,const char *name)
{
	int len;
	int s;
	struct ifreq ifr;

	len = strlen(name);
	if (len > (IFNAMSIZ-1)) {
		perror("tapif_init: name is too long");
		return -1;
	}
	s = socket(AF_INET,SOCK_DGRAM,0);
	if (s == -1) {
		perror("tapif_init: socket");
		return -1;
	}
	memset(&ifr,0,sizeof(ifr));
	strncpy(ifr.ifr_name,name,len);
	if (ioctl(s,SIOCGIFHWADDR,&ifr) == -1) {
		perror("tapif_init: ioctl SIOCGIFHWADDR");
		goto err;
	}
	uint8_t* hwaddr = (uint8_t*)&ifr.ifr_hwaddr.sa_data;
	d->hwaddr[0] = hwaddr[0];
	d->hwaddr[1] = hwaddr[1];
	d->hwaddr[2] = hwaddr[2];
	d->hwaddr[3] = hwaddr[3];
	d->hwaddr[4] = hwaddr[4];
	d->hwaddr[5] = hwaddr[5] ^ 1;
	d->hwaddr_len = 6;
	if (ioctl(s,SIOCGIFMTU,&ifr) == -1) {
		perror("tapif_init: ioctl SIOCGIFMTU");
		goto err;
	}
	d->mtu = ifr.ifr_mtu;
	close(s);
	return 0;
err:
	close(s);
	return -1;
}

static int low_level_output(PCIASNETDevState *d)
{
	/* signal that packet should be sent(); */
	if(write(d->fd, d->txdata, d->txlength) == -1) {
		perror("tapif: write");
		return -1;
	}
	return 0;
}

static int low_level_input(PCIASNETDevState *d)
{
	fd_set fdset;
	int ret;
	struct timeval val = {0 , 0};
	FD_ZERO(&fdset);
	FD_SET(d->fd, &fdset);
	/* Wait for a packet to arrive. */
	ret = select(d->fd + 1, &fdset, NULL, NULL, &val);
	if(ret == 1) {
		d->rxlength = read(d->fd, d->rxdata, sizeof(d->rxdata));
		if(d->rxlength > 0)
		{
			return 0;
		}
	}
	return -1;
}
#endif /* _WIN32 */
static void checkBus(PCIASNETDevState *d)
{
	if(0 == low_level_input(d))
	{
		d->flag |= FLG_RX;
	}
}
#ifdef _WIN32
static void tapif_init(PCIASNETDevState *d,const char* name)
{
	if(low_level_probe(d, name))
	{
		perror("asnet tapif_init failed");
		return;
	}
}
#else  /* _WIN32 */
static void tapif_init(PCIASNETDevState *d,const char* name)
{
	char buf[sizeof(IFCONFIG_ARGS) + sizeof(IFCONFIG_BIN) + 50];
	struct ifreq ifr;
	d->fd = open(DEVTAP, O_RDWR);
	if(d->fd == -1) {
		perror("tapif_init: try running \"modprobe tun\" or rebuilding your kernel with CONFIG_TUN; cannot open "DEVTAP);
		return;
	}

	memset(&ifr, 0, sizeof(ifr));

	if (name != NULL)
	{
		strncpy(ifr.ifr_name,name,strlen(name));
	}

	ifr.ifr_flags = IFF_TAP|IFF_NO_PI;
	if(ioctl(d->fd, TUNSETIFF, (void *) &ifr) < 0) {
		perror("tapif_init: "DEVTAP" ioctl TUNSETIFF");
		return;
	}

	if(low_level_probe(d,name != NULL ? name : ifr.ifr_name))
	{
		perror("asnet low_level_probe failed");
		return;
	}

	if (name == NULL) {
		sprintf(buf, IFCONFIG_BIN IFCONFIG_ARGS,
			ifr.ifr_name,
			ip4_addr1(&(d->gw)),
			ip4_addr2(&(d->gw)),
			ip4_addr3(&(d->gw)),
			ip4_addr4(&(d->gw)),
			ip4_addr1(&(d->netmask)),
			ip4_addr2(&(d->netmask)),
			ip4_addr3(&(d->netmask)),
			ip4_addr4(&(d->netmask)));

		printf("tapif_init: system(\"%s\");\n", buf);
		if(system(buf))
		{
			perror("asnet system\n");
		}
	}
}
#endif /* _WIN32 */
#ifndef __TAPTEST__
static void asnet_iowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size) {

	switch (addr) {
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
	}

}

static uint64_t asnet_ioread(void *opaque, hwaddr addr, unsigned size) {

	switch (addr) {
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
		return 0x0;
	}
}

static uint64_t asnet_mmioread(void *opaque, hwaddr addr, unsigned size) {
	PCIASNETDevState *d = (PCIASNETDevState *) opaque;
	uint64_t val;
	switch (addr) {
	case REG_MACL:
		return (d->hwaddr[0]+(d->hwaddr[1]<<8)+(d->hwaddr[2]<<16)+(d->hwaddr[3]<<24));
		break;
	case REG_MACH:
		return (d->hwaddr[4]+(d->hwaddr[5]<<8));
	case REG_MTU:
		return d->mtu;
		break;
	case REG_DATA:
		assert(d->rxpos < (sizeof(d->rxdata)));
		val = d->rxdata[d->rxpos];
		d->rxpos++;
		return val;
		break;
	case REG_LENGTH:
		d->rxpos = 0;
		val = d->rxlength;
		d->rxlength = 0;
		return val;
		break;
	case REG_NETSTATUS:
		checkBus(d);
		val = d->flag;
		d->flag = 0;
		return val;
		break;
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);
		return 0x0;

	}
}

static void asnet_mmiowrite(void *opaque, hwaddr addr, uint64_t value,
		unsigned size) {
	PCIASNETDevState *d = (PCIASNETDevState *) opaque;

	switch (addr) {
#ifdef _WIN32
	case REG_MACL:
		d->hwaddr[0] = (value >> 0)&0xFF;
		d->hwaddr[1] = (value >> 8)&0xFF;
		d->hwaddr[2] = (value >> 16)&0xFF;
		d->hwaddr[3] = (value >> 24)&0xFF;
		break;
	case REG_MACH:
		d->hwaddr[4] = (value >> 0)&0xFF;
		d->hwaddr[5] = (value >> 8)&0xFF;
		break;
#endif
	case REG_DATA:
		assert(d->txpos < (sizeof(d->txdata)/sizeof(d->txdata[0])));
		d->txdata[d->txpos] = value;
		d->txpos ++;
		break;
	case REG_LENGTH:
		assert(value <= sizeof(d->txdata));
		d->txlength = value;
		d->txpos = 0;
		break;
	case REG_GW:
		d->gw = value;
		break;
	case REG_NETMASK:
		d->netmask = value;
		break;
	case REG_CMD:
		switch (value)
		{
		case 0: /* init */
			if(d->fd > 0)
			{
				printf ("%s: asnet alreay online!\n", __func__);
			}
			else
			{
				tapif_init(d,NULL);
			}
			break;
		case 1: /* TX */
			if(0 == low_level_output(d))
			{
				pci_irq_assert(&d->parent_obj);
			}
			break;
		default:
			printf ("%s: unsupported command 0x%x\n", __func__, (int)value);
		}

		break;
#ifdef _WIN32
	case REG_ADAPTERID:
		d->adapter_num = value;
		break;
#endif
	default:
		printf ("%s: Bad register offset 0x%x\n", __func__, (int)addr);

	}
}

/* Callbacks for MMIO and PIO regions are registered here */
static void asnet_io_setup(PCIASNETDevState *d) {
	memory_region_init_io(&d->mmio, OBJECT(d), &asnet_mmio_ops, d, "asnet_mmio",
			ASNET_MMIO_SIZE);
	memory_region_init_io(&d->io, OBJECT(d), &asnet_io_ops, d, "asnet_io",
			ASNET_IO_SIZE);
}

/* When device is loaded */
static int pci_asnetdev_init(PCIDevice *pci_dev) {
	/* init the internal state of the device */
	PCIASNETDevState *d = PCI_ASNET_DEV(pci_dev);
	d->dma_size = 0x1ffff * sizeof(char);
	d->dma_buf = malloc(d->dma_size);
	d->fd = -1;
	d->rxlength = 0;
#ifdef _WIN32
	d->pcap = NULL;
#endif
	uint8_t *pci_conf;

	/* create the memory region representing the MMIO and PIO
	 * of the device
	 */
	asnet_io_setup(d);
	/*
	 * See linux device driver (Edition 3) for the definition of a bar
	 * in the PCI bus.
	 */
	pci_register_bar(pci_dev, 0, PCI_BASE_ADDRESS_SPACE_IO, &d->io);
	pci_register_bar(pci_dev, 1, PCI_BASE_ADDRESS_SPACE_MEMORY, &d->mmio);

	pci_conf = pci_dev->config;
	/* also in ldd, a pci device has 4 pin for interrupt
	 * here we use pin C.
	 */
	pci_conf[PCI_INTERRUPT_PIN] = 0x03;

	return 0;
}

/* When device is unloaded
 * Can be useful for hot(un)plugging
 */
static void pci_asnetdev_uninit(PCIDevice *dev) {
	PCIASNETDevState *d = (PCIASNETDevState *) dev;
	free(d->dma_buf);
}

static void qdev_pci_asnetdev_reset(DeviceState *dev) {
	PCIASNETDevState *d = (PCIASNETDevState *) dev;

	if(d->fd > 0)
	{
		close(d->fd);
	}

	d->flag = 0;
}

/* Called when the device is defined
 * PCI configuration is defined here
 * We inherit from PCIDeviceClass
 * Also see ldd for the meaning of the different args
 */
static void pci_asnetdev_class_init(ObjectClass *klass, void *data) {
	DeviceClass *dc = DEVICE_CLASS(klass);
	PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);
	k->init = pci_asnetdev_init;
	k->exit = pci_asnetdev_uninit;
	/* this identify our device */
	k->vendor_id = 0xcaac;
	k->device_id = 0x0002;
	k->class_id = PCI_CLASS_OTHERS;
	set_bit(DEVICE_CATEGORY_MISC, dc->categories);

	k->revision = 0x00;
	dc->desc = "PCI ASNET";
	/* qemu user things */
	dc->props = asnet_properties;
	dc->reset = qdev_pci_asnetdev_reset;
}

/* function called before the qemu main
 * it will define our device
 */
static void pci_asnet_register_types(void) {
	type_register_static(&pci_asnet_info);
}
/* ============================ [ FUNCTIONS ] ====================================================== */
/* macro actually defining our device and registering it in qemu*/
type_init(pci_asnet_register_types);
#else /* __TAPTEST__ */
int main(int argc, char* argv[])
{
	PCIASNETDevState d;
	int counter=0;

	memset(&d, 0, sizeof(d));

#ifdef _WIN32
	d.adapter_num = 1;
	d.hwaddr[0] = 0xde;
	d.hwaddr[1] = 0xad;
	d.hwaddr[2] = 0xbe;
	d.hwaddr[3] = 0xef;
	d.hwaddr[4] = 0xde;
	d.hwaddr[5] = 0xad;
#endif
	d.gw=(172<<0)+(18<<8)+(0<<16)+(1<<24);
	d.netmask=(255<<0)+(255<<8)+(255<<16)+(0<<24);

	tapif_init(&d, NULL);
	while(1)
	{
		checkBus(&d);
		if(d.flag&FLG_RX)
		{
			printf("get something %d times\n", counter++);
			d.flag = 0;
			asmem("input", d.rxdata, d.rxlength);
		}
	}
	return 0;
}
#endif /* __TAPTEST__ */
