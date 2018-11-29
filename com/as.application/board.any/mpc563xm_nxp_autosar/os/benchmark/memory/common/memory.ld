/**************************************************************************************
* 
*   Freescale(TM) and the Freescale logo are trademarks of Freescale Semiconductor, Inc. 
*   All other product or service names are the property of their respective owners. 
*   (C) Freescale Semiconductor, Inc. 2008-2009 
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
    OsInternalRAM :  org = 0x40000000, len = 0xC000
}

SECTIONS
{
    /* Interrupt vector table */
    .vects        ALIGN(4K)         : > OsInternalRAM
    /* Code and constant area (all code and constant sections shall be placed between .osbegincode and .osendcode sections) */
    .osbegincode  ALIGN(0x20)       : > .
    .ostext                         : > .
    .oshook                         : > .
    .osrodata                       : > .
    .ossrodata                      : > .
    .appcode                        : > .
    .vletext                        : > .
    .syscall                        : > .
    .secinfo                        : > .
    .rodata                         : > .
    .text                           : > .
    .osendcode                      : > .

    /* OS stack area. This section shall be placed before application data area */
    .osstack      ALIGN(0x20)       : > .  
    .data                           : > .
    .bss                            : > .
    /* OS has no initialized osdata/ossdata; OS does not need clearing of osbss in startup code  */
    .osdata                         : > .
    .osbss                          : > .    
    .app0_vU_bss                    : > .

    /* Default sdata threshold is 0, then sdata/sbss section are empty always. */
    .sdabase      ALIGN(16)         : > .  /* TODO: ALIGN? */
    .sdata                          : > .
    .sapp_var_data                  : > .
    .sbss                           : > .
    .sapp_var_bss                   : > .
    .ossbss                         : > .
    .sdata2                         : > .
    .sapp_vU_bss                    : > .
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
