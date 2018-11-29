ENTRY(_start)

SECTIONS {
/* Entry point of Tinix
 * It must be as same as 'KernelEntryPointPhyAddr' in load.inc!!!
 */
    . = 0x400400;
	.init : {
		KEEP(*(.init))
	}

	.text : {
		*(.text*)
        /* section information for finsh shell */
        . = ALIGN(4);
        __fsymtab_start = .;
        KEEP(*(FSymTab))
        __fsymtab_end = .;
        . = ALIGN(4);
        __vsymtab_start = .;
        KEEP(*(VSymTab))
        __vsymtab_end = .;
        . = ALIGN(4);
        /* section information for modules */
        . = ALIGN(4);
        __rtmsymtab_start = .;
        KEEP(*(RTMSymTab))
        __rtmsymtab_end = .;
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
	}
    _etext = .;

	.data : {
		*(.data*)
	}

	.bss :
	{
		__bss_start = .;	
		*(.bss)
		*(.bss.*)
	}
	__bss_end = .;
    _end = .;

}

