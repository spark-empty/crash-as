/*==================================================================================================

   @file        autosar_os.ld
   @version     2.0.0

   @brief       GHS Linker Command File for Internal FLASH for XPC5607B
   @details     GHS Linker Command File for Internal FLASH for XPC5607B.

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

==================================================================================================*/
MEMORY
{
    bamboot         : org = 0x00000000, len = 0x00000008
    internal_flash  : org = 0x00000008, len = 0x00180000
    int_sram        : org = 0x40000000, len = 0x00017800
}

SECTIONS
{
    /* RAM sections */
    /* OS stack area. This section shall be placed before application data area */
    .osstack                        : > int_sram
    .ramcode                    ABS : > .   /* nedded to placing func in RAM */    
    .PPC.EMB.sdata0             ABS : > .
    .PPC.EMB.sbss0        CLEAR ABS : > .
    /* Default sdata threshold is 0, then sdata/sbss section are empty always. */
    .sdabase      ALIGN(8)          : > .
    .sdata                          : > .
    .sapp_v32_data                  : > .
    .sapp_v16_data                  : > .
    .sapp_vU_data                   : > .
    .sapp_v8_data                   : > .
    .sbss                           : > .
    .ossbss                         : > .
    .sapp_v32_bss                   : > .
    .sapp_v16_bss                   : > .
    .sapp_vU_bss                    : > .
    .sapp_v8_bss                    : > .



    /* Default data/bss */
    .data                           : > .
    .bss                            : > .
    /* OS has no initialized osdata/ossdata; OS does not need clearing of osbss in startup code  */
    .osdata                         : > .
    .osbss                          : > .

    .stack        ALIGN(16) PAD(1K) : > .
    .heap         ALIGN(16)         : > .

    /* ROM sections */
    .rchwdata                       : > bamboot
    /* Code and constant area (all code and constant sections shall be placed between .osbegincode and .osendcode sections) */
    .osbegincode                    : > internal_flash
    .ostext                         : > .
    .oshook                         : > .
    .osrodata                       : > .
    .ossrodata                      : > .
    .vletext                        : > .
    .syscall                        : > .
    .secinfo                        : > .
    .rodata                         : > .
    .sdata2                         : > .
    .sapp_c32                       : > .
    .sapp_c16                       : > .
    .sapp_cU                        : > .
    .sapp_c8                        : > .
    .text                           : > .

    /* Make section .data be burned into flash. It will be copied into RAM during startup
*/
    .ROM.ramcode          ROM(.ramcode) ALIGN(0x10) : > .
    .ROM.PPC.EMB.sdata0        ROM(.PPC.EMB.sdata0) : > .
    .ROM.sdata                          ROM(.sdata) : > .
    .ROM.data                            ROM(.data) : > .

    .appcode                        : > .
    .osendcode                      : > .
    /* mcal configuratins */
    .pbadc_cfg                      : > .
    .pbcan_cfg                      : > .
    .pbdio_cfg                      : > .
    .pbfls_cfg                      : > .
    .pbgpt_cfg                      : > .
    .pbicu_cfg                      : > .
    .pblin_cfg                      : > .
    .pbmcu_cfg                      : > .
    .pbport_cfg                     : > .
    .pbpwm_cfg                      : > .
    .pbspi_cfg                      : > .
    .pbwdg_cfg                      : > .

    /* Interrupt vectors area */
    .vects        ALIGN(64K)         : > .

    __IV_ADDR           = ADDR(.vects);

    INT_SRAM_START      = ADDR(int_sram);
    INT_SRAM_SIZE       = 0x177FF/64;                      
    SBSS_SRAM_START     = ADDR(.sbss);
    SBSS_SRAM_SIZE      = (SIZEOF(.sbss)+3)/4;            // Init 4 bytes at a time
    BSS_SRAM_START      = ADDR(.bss);
    BSS_SRAM_SIZE       = (SIZEOF(.bss)+3)/4;             // Init 4 bytes at a time
    SDATA_RW_START      = _SDA_BASE_;
    SDATA_RO_START      = _SDA2_BASE_;

    RC_RAMCODE_SRC      =  ADDR(.ROM.ramcode);
    RC_RAMCODE_DEST     = ADDR(.ramcode);
    RC_RAMCODE_SIZE     = (SIZEOF(.ROM.ramcode)+3) / 4;         // Copy 4 bytes at a time

    RC_PPC_SDATA2_SRC   = ADDR(.ROM.PPC.EMB.sdata0);
    RC_PPC_SDATA2_DEST  = ADDR(.PPC.EMB.sdata0);
    RC_PPC_SDATA2_SIZE  = (SIZEOF(.ROM.PPC.EMB.sdata0)+3)/4; // Copy 4 bytes at a time
    RC_SDATA_SRC        = ADDR(.ROM.sdata);
    RC_SDATA_DEST       = ADDR(.sdata);
    RC_SDATA_SIZE       = (SIZEOF(.ROM.sdata)+3)/4;          // Copy 4 bytes at a time
    RC_DATA_SRC         = ADDR(.ROM.data);
    RC_DATA_DEST        = ADDR(.data);
    RC_DATA_SIZE        = (SIZEOF(.ROM.data)+3)/4;           // Copy 4 bytes at a time

    _stack_addr = addr(.stack)+sizeof(.stack);
    _stack_end  = addr(.stack);
    _heap_addr  = addr(.heap);
    _heap_end   = addr(.heap)+sizeof(.heap);


    __SP_INIT = _stack_addr;
    __SP_END  = _stack_end;
    __STACK_SIZE = sizeof(.stack);

    /* 2 symbols for ORTI support    */
    _OsOrtiStart      = _stack_addr;
    _OsOrtiStackStart = _stack_end;

    __ghs_rombootcodestart=addr(.osbegincode);
    __ghs_rombootcodeend=addr(.osendcode);
}
