MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M           /* Memory FLASH can be read (r) and executed (x), wiith address origin 0x08000000 and lengh 1MB */
    SRAM1 (wx) : ORIGIN = 0x20000000, LENGTH = 96K          /* Memory SRAM1 can be written (w) and executed (x), wiith address origin 0x20000000 and lengh 96KB */
    SRAM2 (wx) : ORIGIN = 0x10000000, LENGTH = 32K          /* Memory SRAM2 can be written (w) and executed (x), wiith address origin 0x10000000 and lengh 32KB */
}

_stack_start = ORIGIN(SRAM2) + LENGTH(SRAM2);               /* Define the stack started point */

SECTIONS{

    /* Text section for the executed code saved in SRAM1 */
    .text :
    {
        _text_start = .;
        *(.text)               /* All the text section  (The * is for recognize all the sections that match with .text ) */
        _text_end = .;
    } > SRAM1

    /* Read only data section for the constants saved in SRAM1 */
    .rodata :
    {
        _rodata_start = .;
        *(.rodata)             /* All the read only data */
        _data_end = .;
    } > SRAM1

    /* Data section for the initialized variables */
    .data : 
    {
        _data_start = .;
        *(.data)               /* All the data section */
        _data_end = .;
    } > SRAM1

    /* bss section for the non initialized variables */
    .bss : 
    {
        _bss_start = .;
        *(.bss)                /* All the bss section */
        *(COMMON)              /* Comun data between files */
        _bss_end = .;
    } > SRAM1

}

ENTRY(_start)