OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
MEMORY
{
    FLASH (rx) : ORIGIN = 0x40000000, LENGTH = 4K
}

ENTRY(FlashHeader)

SECTIONS
{
    .text :
    {
        *(.rodata.FlashHeader)
        *(.text*)
        *(.rodata*)
    } > FLASH
}