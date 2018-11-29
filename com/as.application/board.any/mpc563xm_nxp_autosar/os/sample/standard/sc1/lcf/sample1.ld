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
    bamboot         : org = 0x00000000, len = 0x00001000 
    internal_flash  : org = 0x00001000, len = 0x000FEFFF
    internal_ram    : org = 0x40000000, len = 0x00010000
}

SECTIONS
{
    .rchwdata                       : > bamboot
    /* Interrupt vectors area */
    .vects        ALIGN(4K)         : > internal_flash
    /* Code and constant area (all code and constant sections shall be placed between .osbegincode and .osendcode sections) */
    .osbegincode                    : > .
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
    /* Make section .data be burned into flash. It will be copied into RAM during startup */
    .ROM.data   ROM(.data)          : > .
    .appcode                        : > .
    .osendcode                      : > .

    /* OS stack area. This section shall be placed before application data area */
    .osstack                        : > internal_ram

    /* Default data/bss */
    .data                           : > .
    .bss                            : > .
    /* OS has no initialized osdata/ossdata; OS does not need clearing of osbss in startup code  */
    .osdata                         : > .
    .osbss                          : > .    

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

    .stack        ALIGN(16) PAD(1K) : > .
    .heap         ALIGN(16)         : > .

    _stack_addr = addr(.stack)+sizeof(.stack);
    _stack_end  = addr(.stack);
    _heap_addr  = addr(.heap);
    _heap_end   = addr(.heap)+sizeof(.heap);
    
    /* 2 symbols for ORTI support    */
    _OsOrtiStart      = _stack_addr;
    _OsOrtiStackStart = _stack_end;

    __ghs_rombootcodestart=addr(.osbegincode);
    __ghs_rombootcodeend=addr(.osendcode);
}
