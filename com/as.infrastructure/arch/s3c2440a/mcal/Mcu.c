/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2015  AS <parai@foxmail.com>
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

#include <assert.h>
#include <string.h>
#include "Std_Types.h"
#include "Mcu.h"
#if defined(USE_DET)
#include "Det.h"
#endif
#if defined(USE_DEM)
#include "Dem.h"
#endif
#include "Os.h"
#include "s3c2440.h"

/* ============================ [ MACROS    ] ====================================================== */
#define TXD0READY   (1<<2)  /* transmit status OK */
#define RXD0READY   (1)     /* receive status OK */

/* uint in 10kHZ */
#define cfgCpuFrequency 40500
#define cfgDivideRatio 9
/* Here cfgDivideRatio:
    if 1,then FCLK:HCLK:PCLK=1:1:2;
    if 2,then FCLK:HCLK:PCLK=1:2:2;
    if 3,then FCLK:HCLK:PCLK=1:2:4;
    if 4,then FCLK:HCLK:PCLK=1:3:3;
    if 5,then FCLK:HCLK:PCLK=1:3:6;
    if 6,then FCLK:HCLK:PCLK=1:6:6;
    if 7,then FCLK:HCLK:PCLK=1:6:12;
    if 8,then FCLK:HCLK:PCLK=1:4:4;
    if 9,then FCLK:HCLK:PCLK=1:4:8;
    if 10,then FCLK:HCLK:PCLK=1:8:8;
    if 11,then FCLK:HCLK:PCLK=1:8:16;
*/

#if(cfgDivideRatio==1)
#define vPCLK_OUT  cfgCpuFrequency/2
#elif(cfgDivideRatio==2)
#define vPCLK_OUT  cfgCpuFrequency/2
#elif(cfgDivideRatio==3)
#define vPCLK_OUT  cfgCpuFrequency/4
#elif(cfgDivideRatio==4)
#define vPCLK_OUT  cfgCpuFrequency/3
#elif(cfgDivideRatio==5)
#define vPCLK_OUT  cfgCpuFrequency/6
#elif(cfgDivideRatio==6)
#define vPCLK_OUT  cfgCpuFrequency/6
#elif(cfgDivideRatio==7)
#define vPCLK_OUT  cfgCpuFrequency/12
#elif(cfgDivideRatio==8)
#define vPCLK_OUT  cfgCpuFrequency/4
#elif(cfgDivideRatio==9)
#define vPCLK_OUT  cfgCpuFrequency/8
#elif(cfgDivideRatio==10)
#define vPCLK_OUT  cfgCpuFrequency/8
#elif(cfgDivideRatio==11)
#define vPCLK_OUT  cfgCpuFrequency/16
#endif

/* Map Get From S3C2440_UM.PDF*/
/* But A Wrong Info in the map table.shit fuck samsung*/
#if(cfgCpuFrequency==27150)
#define cfgMDIV 173
#define cfgPDIV 2
#define cfgSDIV 2
#elif(cfgCpuFrequency==30400)
#define cfgMDIV 68
#define cfgPDIV 1
#define cfgSDIV 1
#elif(cfgCpuFrequency==40500)
#define cfgMDIV 127
#define cfgPDIV 2
#define cfgSDIV 1
#elif(cfgCpuFrequency==53200)
#define cfgMDIV 125
#define cfgPDIV 1
#define cfgSDIV 1
#endif

#if(cfgDivideRatio==1)
#define cfgHDIVN 0
#define cfgPDIVN 1
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==2)
#define cfgHDIVN 1
#define cfgPDIVN 0
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==3)
#define cfgHDIVN 1
#define cfgPDIVN 1
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==4)
#define cfgHDIVN 3
#define cfgPDIVN 0
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==5)
#define cfgHDIVN 3
#define cfgPDIVN 1
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==6)
#define cfgHDIVN 3
#define cfgPDIVN 0
#define cfgHCLK3_HALF 1
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==7)
#define cfgHDIVN 3
#define cfgPDIVN 1
#define cfgHCLK3_HALF 1
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==8)
#define cfgHDIVN 2
#define cfgPDIVN 0
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==9)
#define cfgHDIVN 2
#define cfgPDIVN 1
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 0
#elif(cfgDivideRatio==10)
#define cfgHDIVN 2
#define cfgPDIVN 0
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 1
#elif(cfgDivideRatio==11)
#define cfgHDIVN 2
#define cfgPDIVN 1
#define cfgHCLK3_HALF 0
#define cfgHCLK4_HALF 1
#endif
/*mask for page table base addr*/
#define PAGE_TABLE_L1_BASE_ADDR_MASK	(0xffffc000)

#define VIRT_TO_PTE_L1_INDEX(addr)	(((addr)&0xfff00000)>>18)

#define PTE_L1_SECTION_NO_CACHE_AND_WB	(0x0<<2)
#define PTE_L1_SECTION_DOMAIN_DEFAULT	(0x0<<5)
#define PTE_ALL_AP_L1_SECTION_DEFAULT	(0x1<<10)

#define PTE_L1_SECTION_PADDR_BASE_MASK	(0xfff00000)
#define PTE_BITS_L1_SECTION				(0x2)

#define L1_PTR_BASE_ADDR			0x30700000
#define PHYSICAL_MEM_ADDR			0x30000000
#define VIRTUAL_MEM_ADDR			0x30000000
#define MEM_MAP_SIZE				0x00800000
#define PHYSICAL_IO_ADDR			0x48000000
#define VIRTUAL_IO_ADDR				0x48000000
#define IO_MAP_SIZE					0x18000000
#define VIRTUAL_VECTOR_ADDR			0x0
#define PHYSICAL_VECTOR_ADDR		0x30000000
/* ============================ [ TYPES     ] ====================================================== */
/* ============================ [ DECLARES  ] ====================================================== */
/* ============================ [ DATAS     ] ====================================================== */
/* ============================ [ LOCALS    ] ====================================================== */
static void Usart_Init(void)
{
	GPHCON |= 0xa0;    /* GPH2,GPH3 used as TXD0,RXD0 */
	GPHUP     = 0x0;   /* GPH2,GPH3 pull up */
	ULCON0  = 0x03;    /* 8N1         */
	UCON0     = 0x05;  /* poll or interrupt; select clock PCLK */
	UFCON0 = 0x00;     /* no FIFO */
	UMCON0 = 0x00;     /* no flow control */
    /* UBRDIVn=(int)(UART clock)/(baud rate*16)-1*/
	UBRDIV0 = (vPCLK_OUT*10000)/(56700*16)-1;      /* PCLK=12Mhz */
}


void start_mmu(void){
	unsigned int ttb=L1_PTR_BASE_ADDR;
	asm (
		"mcr p15,0,%0,c2,c0,0\n"    /* set base address of page table*/
		"mvn r0,#0\n"
		"mcr p15,0,r0,c3,c0,0\n"    /* enable all region access*/

		"mov r0,#0x1\n"
		"mcr p15,0,r0,c1,c0,0\n"    /* set back to control register */
		"mov r0,r0\n"
		"mov r0,r0\n"
		"mov r0,r0\n"
		:
		: "r" (ttb)
		:"r0"
	);
}
/*
start_mmu
	EXPORT start_mmu
    ;asm volatile("mov r0,#L1_PTR_BASE_ADDR
    LDR r0,=0x30700000
    mcr p15,0,r0,c2,c0,0          ;set base address of page table
    mvn r0,#0
    mcr p15,0,r0,c3,c0,0          ;enable all region access

	mrc p15,0,r0,c1,c0,0
    orr r0,r0,#0x1
    mcr p15,0,r0,c1,c0,0          ;set back to control register
	bx  lr
*/
static unsigned int gen_l1_pte(unsigned int paddr){
	return (paddr&PTE_L1_SECTION_PADDR_BASE_MASK)|\
										PTE_BITS_L1_SECTION;
}

static unsigned int gen_l1_pte_addr(unsigned int baddr,\
										unsigned int vaddr){
	return (baddr&PAGE_TABLE_L1_BASE_ADDR_MASK)|\
								VIRT_TO_PTE_L1_INDEX(vaddr);
}

static void init_sys_mmu(void){
	unsigned int pte;
	unsigned int pte_addr;
	int j;

	for(j=0;j<MEM_MAP_SIZE>>20;j++){
		pte=gen_l1_pte(PHYSICAL_VECTOR_ADDR+(j<<20));
		pte|=PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte|=PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte|=PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr=gen_l1_pte_addr(L1_PTR_BASE_ADDR,\
								VIRTUAL_VECTOR_ADDR+(j<<20));
		*(volatile unsigned int *)pte_addr=pte;
	}
	for(j=0;j<MEM_MAP_SIZE>>20;j++){
		pte=gen_l1_pte(PHYSICAL_MEM_ADDR+(j<<20));
		pte|=PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte|=PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte|=PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr=gen_l1_pte_addr(L1_PTR_BASE_ADDR,\
								VIRTUAL_MEM_ADDR+(j<<20));
		*(volatile unsigned int *)pte_addr=pte;
	}
	for(j=0;j<IO_MAP_SIZE>>20;j++){
		pte=gen_l1_pte(PHYSICAL_IO_ADDR+(j<<20));
		pte|=PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte|=PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte|=PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr=gen_l1_pte_addr(L1_PTR_BASE_ADDR,\
								VIRTUAL_IO_ADDR+(j<<20));
		*(volatile unsigned int *)pte_addr=pte;
	}
}

static void remap_l1(unsigned int paddr,unsigned int vaddr,int size){
	unsigned int pte;
	unsigned int pte_addr;
	for(;size>0;size-=1<<20){
		pte=gen_l1_pte(paddr);
		pte_addr=gen_l1_pte_addr(L1_PTR_BASE_ADDR,vaddr);
		*(volatile unsigned int *)pte_addr=pte;
	}
}
/* ============================ [ FUNCTIONS ] ====================================================== */
void __putchar(char ch)
{
	while( ! (UTRSTAT0 & TXD0READY) );
	UTXH0 = ch;
}

#ifndef __GNUC__
int putchar( int ch )	/* for printf */
{
	__putchar(ch);
  return ch;
}
#endif
void Mcu_Init(const Mcu_ConfigType *configPtr)
{
	(void)configPtr;
}

void Mcu_SetMode( Mcu_ModeType McuMode ) {
	(void)McuMode;
}

/**
 * Get the system clock in Hz. It calculates the clock from the
 * different register settings in HW.
 */
uint32_t McuE_GetSystemClock(void)
{
  return (vPCLK_OUT*10*1000);
}
Std_ReturnType Mcu_InitClock( const Mcu_ClockType ClockSetting ) {
	(void)ClockSetting;
    /* Set U_LTIME[31:16] = 0xFFFF,M_LTIME[15:0]=0xFFFF*/
	LOCKTIME=0xFFFFFFFF;
    CLKDIVN=(cfgHDIVN<<1)|cfgPDIVN;
    /* As CAMDIVN's initial is 0 so ...*/
    CAMDIVN=(cfgHCLK4_HALF<<9)|(cfgHCLK3_HALF<<8);
    /* FCLK=Mpll=(2*m*Fin)/(p*2^s);
       FVCO=(2*m*Fin)/p,where 600MHZ<=FVCp<=1.2GHZ;
       200MHZ<=FCLK<=600MHZ;
       1<=MDIV<=248,1<=PDIV<=62
       Fin=12MHZ;
       m=(MDIV+8),p=(PDIV+2),s=SDIV */
    MPLLCON=(cfgMDIV<<12)|(cfgPDIV<<4)|(cfgSDIV);
    return E_OK;
}

void Mcu_PerformReset( void ) {

}

Mcu_PllStatusType Mcu_GetPllStatus( void ) {
	return MCU_PLL_LOCKED;
}


Mcu_ResetType Mcu_GetResetReason( void )
{
	return MCU_POWER_ON_RESET;
}

void Mcu_DistributePllClock( void )
{
	init_sys_mmu();
	start_mmu();
	Usart_Init();
}

#ifdef __AS_BOOTLOADER__
void StartOsTick(void) {
	/* timer4, pre = 15+1 */
	TCFG0 &= 0xffff00ff;
	TCFG0 |= 15 << 8;
	/* all are interrupt mode,set Timer 4 MUX 1/4 */
	TCFG1  &= 0xfff0ffff;
	TCFG1  |= 0x00010000;

	TCNTB4 = (uint32_t)(McuE_GetSystemClock() / (4 *16* 1000)) - 1;	/* 1000 ticks per second */
	/* manual update */
	TCON = TCON & (~(0x0f<<20)) | (0x02<<20);

	/* enable interrupt */
	INTMSK &= ~BIT_TIMER4;

    /* start timer4, reload */
	TCON = TCON & (~(0x0f<<20)) | (0x05<<20);
}

void knl_isr_handler(void)
{
	 uint32_t intno;

	intno = INTOFFSET;
	if(14 == intno)
	{
		OsTick();
	}
	else
	{
		while(1);
	}

	/* clear interrupt */
	if(intno < 32)
	{
		SRCPND |= (1<<intno);
		INTPND = INTPND;
	}
	else if(intno < 46)
	{
		SUBSRCPND |= (1<<(intno-32));
	}
}
#endif
