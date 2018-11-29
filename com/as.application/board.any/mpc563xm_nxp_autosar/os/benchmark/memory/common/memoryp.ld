/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2008 - 2010
* 
*   You can use this example for any purpose on any computer system with the
*   following restrictions:
*
*   1. This example is provided "as is", without warranty.
*
*   2. You don't remove this copyright notice from this example or any direct derivation 
*      thereof.
*
*  Description:  Green Hills linker command file for AUTOSAR OS/MPC56xxAM benchmark
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
    /* Interrupt vector table */
    .vects        ALIGN(4K)         : > OsInternalRAM
    /* Code and constant area (all code and constant sections shall be placed between .osbegincode and .osendcode sections) */
    .osbegincode                    : > .
    .ostext                         : > .
    .oshook                         : > .
    .osrodata                       : > .
    .ossrodata                      : > .
    .appcode                        : > .
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
    .osendcode                      : > .

    /* OS stack area. This section shall be placed before application data area */
    .osstack      ALIGN(0x20)       : > .  

/* Begin of the RAM area for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
/* End of the RAM area for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */

/* Begin of the RAM area #1 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */ 
/* End of the RAM area #1 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */

/* Begin of the RAM area #2 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */ 
/* End of the RAM area #2 for applications. Do not edit or delete this comment: it is used by the SysGen for GHS */
    
    /* Default data/bss */
    .data                           : > .
    .bss                            : > .
    /* OS has no initialized osdata/ossdata; OS does not need clearing of osbss in startup code  */
    .osdata                         : > .
    .osbss                          : > .    

    /* Default sdata threshold is 0, then sdata/sbss section are empty always. */
    .sdabase      ALIGN(16)         : > .  /* TODO: ALIGN? */
    .sdata                          : > .
    .sapp_var_data                  : > .
    .sbss                           : > .
    .sapp_var_bss                   : > .
    .ossbss                         : > .
    .sapp_v32_bss                   : > .
    .sapp_v16_bss                   : > .
    .sapp_vU_bss                    : > .
    .sapp_v8_bss                    : > .
    .sbss2                          : > .
    .stack  ALIGN(16)  PAD(1K)      : > .
/*    .heap         ALIGN(16)         : > . */

    _stack_addr = addr(.stack)+sizeof(.stack);
    _stack_end  = addr(.stack);
/*    _heap_addr  = addr(.heap); */
/*    _heap_end   = addr(.heap)+sizeof(.heap); */
/* 2 symbols for ORTI support    */

    _OsOrtiStart      = _stack_addr;
    _OsOrtiStackStart = _stack_end;

}
