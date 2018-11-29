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
 */
#ifdef USE_PCI
/* http://infocenter.arm.com/help/topic/com.arm.doc.dui0224i/DUI0224I_realview_platform_baseboard_for_arm926ej_s_ug.pdf
 * 3.15 PCI interface  p141
 * 4.17 PCI controller p241
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#define IO_VALUE_FIRST
#include "Std_Types.h"
#include "asdebug.h"
#include "pci_core.h"
#ifndef USE_STDRT
#include "irq.h"
#else
#include <rtthread.h>
#include <rthw.h>
#include "interrupt.h"
#endif
/* ============================ [ MACROS    ] ====================================================== */
#define AS_LOG_PCI 1

#define PCI_IMAP(m)		(versatile_pci_base + ((m) * 4))
#define PCI_SMAP(m)		(versatile_pci_base + 0x14 + ((m) * 4))
#define PCI_SELFID		(versatile_pci_base + 0xc)

#define VP_PCI_DEVICE_ID		0x030010ee
#define VP_PCI_CLASS_ID			0x0b400000

#define PHYS_OFFSET 0
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* according to https://github.com/qemu/qemu/blob/master/hw/arm/versatilepb.c */
static void *versatile_pci_base = (void *)0x10001000;
static void *versatile_cfg_base[2] = { (void *)0x41000000, (void *)0x42000000 };
static u32 pci_slot_ignore;
/* ============================ [ LOCALS    ] ====================================================== */
static void *versatile_map_bus(unsigned int busnr,
				       unsigned int devfn, int offset)
{
	if (pci_slot_ignore & (1 << PCI_SLOT(devfn)))
		return NULL;

	return versatile_cfg_base[1] + ((busnr << 16) | (devfn << 8) | offset);
}

static int versatile_pci_probe(void)
{
	int ret, i, myslot = -1;
	u32 val;
	void *local_pci_cfg_base;
	/* according to http://elixir.free-electrons.com/linux/v4.8/source/arch/arm/boot/dts/versatile-pb.dts */
	/* downstream I/O */
	/* TODO: pci_remap_iospace(res, 0x43000000);
	 * MMU is not implemented, so can't map  IO 0x43000000..0x4300ffff -> 0x00000000
	 */
	//writel(0x43000000 >> 28, PCI_IMAP(0));
	//writel(PHYS_OFFSET >> 28, PCI_SMAP(0));
	/* non-prefetchable memory */
	writel(0x50000000 >> 28, PCI_IMAP(1));
	writel(PHYS_OFFSET >> 28, PCI_SMAP(1));
	/* prefetchable memory */
	writel(0x60000000 >> 28, PCI_IMAP(2));
	writel(PHYS_OFFSET >> 28, PCI_SMAP(2));
	/*
	 * We need to discover the PCI core first to configure itself
	 * before the main PCI probing is performed
	 */
	for (i = 0; i < 32; i++) {
		if ((readl(versatile_cfg_base[0] + (i << 11) + PCI_VENDOR_ID) == VP_PCI_DEVICE_ID) &&
		    (readl(versatile_cfg_base[0] + (i << 11) + PCI_CLASS_REVISION) == VP_PCI_CLASS_ID)) {
			myslot = i;
			break;
		}
	}
	if (myslot == -1) {
		ASLOG(PCI, "Cannot find PCI core!\n");
		return -__LINE__;
	}
	/*
	 * Do not to map Versatile FPGA PCI device into memory space
	 */
	pci_slot_ignore |= (1 << myslot);

	ASLOG(PCI, "PCI core found (slot %d)\n", myslot);

	writel(myslot, PCI_SELFID);
	local_pci_cfg_base = versatile_cfg_base[1] + (myslot << 11);

	val = readl(local_pci_cfg_base + PCI_COMMAND);
	val |= PCI_COMMAND_MEMORY | PCI_COMMAND_MASTER | PCI_COMMAND_INVALIDATE;
	writel(val, local_pci_cfg_base + PCI_COMMAND);

	/*
	 * Configure the PCI inbound memory windows to be 1:1 mapped to SDRAM
	 */
	writel(PHYS_OFFSET, local_pci_cfg_base + PCI_BASE_ADDRESS_0);
	writel(PHYS_OFFSET, local_pci_cfg_base + PCI_BASE_ADDRESS_1);
	writel(PHYS_OFFSET, local_pci_cfg_base + PCI_BASE_ADDRESS_2);

	/*
	 * For many years the kernel and QEMU were symbiotically buggy
	 * in that they both assumed the same broken IRQ mapping.
	 * QEMU therefore attempts to auto-detect old broken kernels
	 * so that they still work on newer QEMU as they did on old
	 * QEMU. Since we now use the correct (ie matching-hardware)
	 * IRQ mapping we write a definitely different value to a
	 * PCI_INTERRUPT_LINE register to tell QEMU that we expect
	 * real hardware behaviour and it need not be backwards
	 * compatible for us. This write is harmless on real hardware.
	 */
	writel(0, versatile_cfg_base[0] + PCI_INTERRUPT_LINE);

	return 0;
}

/* ============================ [ FUNCTIONS ] ====================================================== */
int pci_init(void)
{
	int rv;

	rv = versatile_pci_probe();

	return rv;
}

int pci_generic_config_write(unsigned int busnr, unsigned int devfn,
			     int where, int size, u32 val)
{
	void *addr;

	addr = versatile_map_bus(busnr, devfn, where);
	if (!addr)
	{
		return -__LINE__;
	}
	if (size == 1)
		writeb(val, addr);
	else if (size == 2)
		writew(val, addr);
	else
		writel(val, addr);

	return 0;
}

int pci_generic_config_read(unsigned int busnr, unsigned int devfn,
			      int where, int size, u32 *val)
{
	void *addr;

	addr = versatile_map_bus(busnr, devfn, where & ~0x3);

	if (!addr) {
		*val = ~0;
		return -__LINE__;
	}

	*val = readl(addr);

	if (size <= 2)
		*val = (*val >> (8 * (where & 3))) & ((1 << (size * 8)) - 1);

	return 0;
}

/* Lunatic */
uint32 pci_read_config_reg32(pci_reg *reg, uint8 offset)
{
    uint32 value;
	
	pci_generic_config_read(reg->bus, reg->fn, offset|(reg->dev<<11), 4, &value);
    
    return value;
}

uint16 pci_read_config_reg16(pci_reg *reg, uint8 offset)
{
	uint32 value;
	
	pci_generic_config_read(reg->bus, reg->fn, offset|(reg->dev<<11), 2, &value);
    
    return (uint16)value;
}

uint8 pci_read_config_reg8(pci_reg *reg, uint8 offset)
{
	uint32 value;
	
	pci_generic_config_read(reg->bus, reg->fn, offset|(reg->dev<<11), 1, &value);
    
    return (uint8)value;
}

void pci_write_config_reg32(pci_reg *reg, uint8 offset, const uint32 value)
{
	pci_generic_config_write(reg->bus, reg->fn, offset|(reg->dev<<11), 4, value);
}

void pci_write_config_reg16(pci_reg *reg, uint8 offset ,const uint16 value)
{
	pci_generic_config_write(reg->bus, reg->fn, offset|(reg->dev<<11), 2, value);
}

void pci_write_config_reg8(pci_reg *reg, uint8 offset, const uint8 value)
{
	pci_generic_config_write(reg->bus, reg->fn, offset|(reg->dev<<11), 1, value);
}

#ifndef USE_STDRT
int pci_disable_IRQ_line(uint32 irq) { irq_disable_line(irq); return 0; }
int pci_enable_IRQ_line(uint32 irq)  { irq_enable_line(irq); return 0; }
int pci_sys_set_irq_handle(uint32 irq, void(*handle)(void)) { return irq_install_isr(irq,(isr_callback_t)handle); }
#else
int pci_disable_IRQ_line(uint32 irq) { rt_hw_interrupt_mask(irq); return 0; }
int pci_enable_IRQ_line(uint32 irq)  { rt_hw_interrupt_unmask(irq); return 0; }
int pci_sys_set_irq_handle(uint32 irq, void(*handle)(void)) { return 	rt_hw_interrupt_install(irq, handle, RT_NULL, "pci"); }
#endif
int pci_sys_irq_set_level_trigger(uint32 irq) { return 1; }
int pci_sys_irq_set_edge_trigger(uint32 irq)  { return 1; }

#endif
