/*==================================================================================================

   @file        autosar_flash.ld
   @version     2.0.0

   @brief       GHS Linker Command File for Internal FLASH for XPC564XA
   @details     GHS Linker Command File for Internal FLASH for XPC564XA.

   Project      : AUTOSAR 3.0 MCAL
   Patform      : PA
   Peripheral   : 
   Dependencies : Base Det Dem Port Dio Mcu SchM Wdg WdgIf CanIf LinIf EcuM

   Autosar Version       : 1.9.0
   Autosar Revision      : ASR_REL_1_9_REV_0003
   Autosar Conf. Variant :
   Software Version      : 2.0.0
   Build Version         : MPC563xMxM_MCAL_2_0_0_RTM_ASR_REL_1_9_REV_0003_20110214

   (c) Copyright 2006-2011 Freescale Semiconductor Inc. & STMicroelectronics
   All Rights Reserved.

===================================================================================================

Note: This linker command file to be used with XPC564XA devices only.
==================================================================================================*/

MEMORY {

    /* XPC563XM - Flash 1.5 MB - 0x00 - 0x17FFFF */

    flash_rsvd1         : ORIGIN = 0x00000000, LENGTH = 8
    flash_memory        : ORIGIN = 0x00000008, LENGTH = 0xEFFF8
    flash_vec           : ORIGIN = 0x000F0000, LENGTH = 0x90000
    flash_rsvd2         : ORIGIN = .,          LENGTH = 0

    /* XPC563XM - SRAM 94 KB : 0x40000000 - 0x400177FF */

    ram_rsvd1           : ORIGIN = 0x20000000, LENGTH = 0
    int_sram        :     origin = 0x40000000, length = 0x163A0
    res_ram         :     origin = 0x400163A0, LENGTH = 0x20    
    iram_stack      :     origin = 0x400163C0, length = 0x01000
    int_timers      :     origin = 0x400173C0, length = 0x0340
    int_results         : ORIGIN = 0x40017700, LENGTH = 0x100
    ram_rsvd2           : ORIGIN = .,          LENGTH = 0

}

//
// Program layout for starting in ROM, copying data to RAM,
// and continuing to execute out of ROM.
//

SECTIONS
{
//
// RAM SECTIONS
//
    .ramcode                                    ABS : > int_sram   /* nedded to placing func in RAM */
    .PPC.EMB.sdata0                             ABS : > .
    .PPC.EMB.sbss0                        CLEAR ABS : > .

    .sdabase                               ALIGN(8) : > .
    .sdata                                          : > .
    .sbss                                           : > .
    .data                                           : > .
    .bss                                            : > .

//
// ROM SECTIONS
//
    .rcw                                            : > flash_rsvd1
    .text                                           : > flash_memory
    .vletext                                        : > .
    .syscall                                        : > .
    .rodata                                         : > .
    .sdata2                                         : > .
    .secinfo                                        : > .
    .fixaddr                                        : > .
    .fixtype                                        : > .

    .ROM.ramcode          ROM(.ramcode) ALIGN(0x10) : > .
    .ROM.PPC.EMB.sdata0        ROM(.PPC.EMB.sdata0) : > .
    .ROM.sdata                          ROM(.sdata) : > .
    .ROM.data                            ROM(.data) : > .

    .pbadc_cfg                                      : > flash_memory
    .pbcan_cfg                                      : > flash_memory
    .pbdio_cfg                                      : > flash_memory
    .pbfls_cfg                                      : > flash_memory
    .pbgpt_cfg                                      : > flash_memory
    .pbicu_cfg                                      : > flash_memory
    .pblin_cfg                                      : > flash_memory
    .pbmcu_cfg                                      : > flash_memory
    .pbport_cfg                                     : > flash_memory
    .pbpwm_cfg                                      : > flash_memory
    .pbspi_cfg                                      : > flash_memory
    .pbwdg_cfg                                      : > flash_memory
    .isrvectbl                        ALIGN(0x1000) : > flash_vec
    .isrvectbl_core                                 : > .

//
// These special symbols mark the bounds of RAM and ROM memory.
// They are used by the MULTI debugger.
//
    __ghs_ramstart      = MEMADDR(ram_rsvd1);
    __ghs_ramend        = MEMENDADDR(ram_rsvd2);
    __ghs_romstart      = MEMADDR(flash_rsvd1);
    __ghs_romend        = MEMENDADDR(flash_rsvd2);

    __IV_ADDR           = MEMADDR(flash_vec);

    PB_ADC_CFG1         = ADDR(.pbadc_cfg);
    PB_CAN_CFG1         = ADDR(.pbcan_cfg);
    PB_DIO_CFG1         = ADDR(.pbdio_cfg);
    PB_FLS_CFG1         = ADDR(.pbfls_cfg);
    PB_GPT_CFG1         = ADDR(.pbgpt_cfg);
    PB_ICU_CFG1         = ADDR(.pbicu_cfg);
    PB_LIN_CFG1         = ADDR(.pblin_cfg);
    PB_MCU_CFG1         = ADDR(.pbmcu_cfg);
    PB_PORT_CFG1        = ADDR(.pbport_cfg);
    PB_PWM_CFG1         = ADDR(.pbpwm_cfg);
    PB_SPI_CFG1         = ADDR(.pbspi_cfg);
    PB_WDG_CFG1         = ADDR(.pbwdg_cfg);

    INT_SRAM_START      = ADDR(int_sram);
    INT_SRAM_SIZE       = 0x177FF/64;                      


    SBSS_SRAM_START     = ADDR(.sbss);
    SBSS_SRAM_SIZE      = (SIZEOF(.sbss)+3)/4;            // Init 4 bytes at a time
    BSS_SRAM_START      = ADDR(.bss);
    BSS_SRAM_SIZE       = (SIZEOF(.bss)+3)/4;             // Init 4 bytes at a time
    SDATA_RW_START      = ADDR(.sdata);
    SDATA_RO_START      = ADDR(.sdata2);
    RC_RAMCODE_SRC =  ADDR(.ROM.ramcode);
    RC_RAMCODE_DEST = ADDR(.ramcode);
    RC_RAMCODE_SIZE = (SIZEOF(.ROM.ramcode)+3) / 4;         // Copy 4 bytes at a time

    RC_PPC_SDATA2_SRC   = ADDR(.ROM.PPC.EMB.sdata0);
    RC_PPC_SDATA2_DEST  = ADDR(.PPC.EMB.sdata0);
    RC_PPC_SDATA2_SIZE  = (SIZEOF(.ROM.PPC.EMB.sdata0)+3)/4; // Copy 4 bytes at a time
    RC_SDATA_SRC        = ADDR(.ROM.sdata);
    RC_SDATA_DEST       = ADDR(.sdata);
    RC_SDATA_SIZE       = (SIZEOF(.ROM.sdata)+3)/4;          // Copy 4 bytes at a time
    RC_DATA_SRC         = ADDR(.ROM.data);
    RC_DATA_DEST        = ADDR(.data);
    RC_DATA_SIZE        = (SIZEOF(.ROM.data)+3)/4;           // Copy 4 bytes at a time

    __SP_INIT           = ADDR(iram_stack) + SIZEOF(iram_stack);
    __SP_END            = ADDR(iram_stack);
    __STACK_SIZE        = SIZEOF(iram_stack);
    
    _ERASE_FUNC_ADDRESS_            = ADDR(res_ram);
    _WRITE_FUNC_ADDRESS_            = ADDR(res_ram);

}
