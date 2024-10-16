MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M           /* Memory FLASH can be read (r) and executed (x), wiith address origin 0x08000000 and lengh 1MB */
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96k          /* Memory SRAM1 can be written (w) and executed (x), wiith address origin 0x20000000 and lengh 96KB */
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32k          /* Memory SRAM2 can be written (w) and executed (x), wiith address origin 0x10000000 and lengh 32KB */
}

SECTIONS{

    /* Text section for the executed code saved in SRAM1 */
    .text :
    {
        *(.text)               /* All the text section  (The * is for recognize all the sections that match with .text ) */
    } > SRAM1

    /* Read only data section for the constants saved in SRAM1 */
    .rodata :
    {
        *(.rodata)             /* All the read only data */
    } > SRAM1

    /* Data section for the initialized variables */
    .data : 
    {
        *(.data)               /* All the data section */
    } > SRAM1

    /* bss section for the non initialized variables */
    bss : 
    {
        __bss_start__ = .;
        *(.bss)                /* All the bss section */
        *(COMMON)               /* Comun data between files */
        __bss_end__ = .;
    } > SRAM1

}

ENTRY(main)