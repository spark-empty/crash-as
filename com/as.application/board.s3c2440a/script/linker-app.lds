/* Linker script to configure memory regions. 
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */
OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
    /* All is DRAM space */
    FLASH (rx)  : ORIGIN = 0x30100000, LENGTH = 4M  
    RAM  (rwx)  : ORIGIN = 0x30500000, LENGTH = 5M 
	IRAM (rwx)  : ORIGIN = 0x40000000, LENGTH = 4K  
}

ENTRY(_start)

knl_system_stack_size = 4096;

SECTIONS
{
	.text :
	{
	    *(.startup*)
		*(.text*)
		__ctors_start__ = .;
		*(.ctors*)
		__ctors_end__ = .;
		/* section information for shell */
		. = ALIGN(4);
		__ssymtab_start = .;
		KEEP(*(SSymTab))
		__ssymtab_end = .;
		/* section information for ELF Symbols */
		. = ALIGN(4);
		__elfsymtab_start = .;
		KEEP(*(ELFSymTab))
		__elfsymtab_end = .;
		*(.rodata*)
	} > FLASH

	__etext = .;
		
	.data : AT (__etext)
	{
		. = ALIGN(4);
		__data_start__ = .;
		*(.data*)
		__data_end__ = .;
	} > RAM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		__bss_end__ = .;
	} > RAM
	
	.init_stack ALIGN(16) (NOLOAD) : 
	{	
		knl_irq_stack_start = .;
	    . = . + 2048;  
	    knl_irq_stack_top = .;
		
		knl_fiq_stack_start = .; 
		. = . + 2048; 	
		knl_fiq_stack_top = .;
		
		knl_undefined_stack_start = .;
        . = . + 2048;   
        knl_undefined_stack_top = .;
		
		knl_aboknl_stack_start = .;
        . = . + 2048;   
        knl_aboknl_stack_top = .;
		
		/* svc stack */
        knl_system_stack    = .;
        . = . + knl_system_stack_size;   
        knl_system_stack_top = .;
	} > RAM
}
