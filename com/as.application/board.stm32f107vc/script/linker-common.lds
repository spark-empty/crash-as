/* Linker script to configure memory regions. 
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   RAM.ORIGIN: starting address of RAM bank 0
 *   RAM.LENGTH: length of RAM bank 0
 */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}


ENTRY(reset_handler)

knl_system_stack_size = 1024;

SECTIONS
{
	.text :
	{
	   KEEP(*(.isr_vector))
	   *(.startup*)
        *(.text*)
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
        . = ALIGN(4);
        autostart_processes = .;
        KEEP(*(ProtoSymTab))
        KEEP(*(ProtoSymTabEnd))
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
	   knl_system_stack    = .; 
	   . = . + knl_system_stack_size; 	
	   knl_system_stack_top = .;
	} > RAM
}
