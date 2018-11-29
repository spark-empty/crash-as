/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2009-2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*  Description:  Green Hills linker command file for AUTOSAR OS/MPC56xxAMv3 sample 
*                application.
*
**************************************************************************************/
MEMORY
{
/* The memory areas for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
/* The end of the memory areas for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
}

SECTIONS
{
    /* Interrupt vectors area */
    .vects        ALIGN(4K)              : > OsInternalRAM


    /* Code and constant area (all code and constant sections shall be placed between .osbegincode and .osendcode sections) */
    .osbegincode  ALIGN(0x20)            : > .
    .ostext       ALIGN(0x8)             : > .
    .oshook       ALIGN(0x8)             : > .
    .osrodata     ALIGN(0x8)             : > .
    .ossrodata    ALIGN(0x8)             : > .
    .vletext      ALIGN(0x8)             : > .
    .syscall      ALIGN(0x8)             : > .
    .secinfo      ALIGN(0x8)             : > .
    .rodata       ALIGN(0x8)             : > .
    .sdata2       ALIGN(0x8)             : > .
    .sapp_c32     ALIGN(0x8)             : > .
    .sapp_c16     ALIGN(0x8)             : > .
    .sapp_cU      ALIGN(0x8)             : > .
    .sapp_c8      ALIGN(0x8)             : > .
    .text         ALIGN(0x8)             : > .
    .appcode      ALIGN(0x8)             : > .
    .osendcode    ALIGN(0x20)            : > .


    /* OS stack area. This section shall be placed before application data area */
    .osstack      ALIGN(0x20)            : > OsInternalRAM

    /* Begin of the RAM area for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
    /* End of the RAM area for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */

    /* Begin of the RAM area #1 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
    /* End of the RAM area #1 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */

    /* Begin of the RAM area #2 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
    /* End of the RAM area #2 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */

    /* Default data/bss */
    .data         ALIGN(0x8)             : > . 
    .bss                                 : > .

    /* OS has no initialized osdata/ossdata; OS does not need clearing of osbss in startup code  */
    .osdata                              : > .
    .osbss                               : > .    

    /* Default sdata threshold is 0, then sdata/sbss section are empty always. */
    .sdabase      ALIGN(8)               : > .
    .sdata                               : > .
    .sapp_v32_data                       : > .
    .sapp_v16_data                       : > .
    .sapp_vU_data                        : > .
    .sapp_v8_data                        : > .
    .sbss                                : > .
    .ossbss                              : > .
    .sapp_v32_bss                        : > .
    .sapp_v16_bss                        : > .
    .sapp_vU_bss                         : > .
    .sapp_v8_bss                         : > .

    .stack        ALIGN(16) PAD(1K)      : > .
    .heap         ALIGN(16)              : > .

    _stack_addr = addr(.stack)+sizeof(.stack);
    _stack_end  = addr(.stack);
    _heap_addr  = addr(.heap);
    _heap_end   = addr(.heap)+sizeof(.heap);
    
    /* 2 symbols for ORTI support    */
    _OsOrtiStart      = _stack_addr;
    _OsOrtiStackStart = _stack_end;

    __ghs_ramstart  = addr(OsInternalRAM);
    __ghs_ramend    = addr(OsInternalRAM) + sizeof(OsInternalRAM);
    __ghs_romstart  = addr(OsInternalROM);
    __ghs_romend    = addr(OsInternalROM) + sizeof(OsInternalROM);

    __ghs_rambootcodestart  = 0;
    __ghs_rambootcodeend    = 0;
    __ghs_rombootcodestart=addr(.osbegincode);
    __ghs_rombootcodeend=addr(.osendcode);
}
