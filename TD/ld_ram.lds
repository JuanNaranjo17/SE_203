MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1M           /* Memory FLASH can be read (r) and executed (x), wiith address origin 0x08000000 and lengh 1MB */
    SRAM1 (rwx) : ORIGIN = 0x20000000, LENGTH = 96K          /* Memory SRAM1 can be read(r) written (w) and executed (x), wiith address origin 0x20000000 and lengh 96KB */
    SRAM2 (rwx) : ORIGIN = 0x10000000, LENGTH = 32K          /* Memory SRAM2 can be read(r) written (w) and executed (x), wiith address origin 0x10000000 and lengh 32KB */
}

_stack_start = ORIGIN(SRAM2) + LENGTH(SRAM2);               /* Define the stack started point */

_text_src = LOADADDR(.text);                                /* Define the text section location in flash */
_isr_src = LOADADDR(.isr_vector);                           /* Define the isr_vector section location in FLASH */
_data_src = LOADADDR(.data);                                /* Define the data section location in flash */

SECTIONS{

    /* Vector table initialize section (should be in FLASH) */
    .isr_init : {
		*(.isr_init)
	} > FLASH

    /* Vector table section (should be in SRAM1 for allow the own handlers implementation) */
    .isr_vector :
    {
        _isr_start = .;
        KEEP(*(.isr_vector))   /* Keep the vector table section */
        _isr_end = .;
    } > SRAM1 AT > FLASH       /* The isr_vector section is located and executed in SRAM1 but is copy to FLASH at compilation */

    /* Code executed in FLASH that copy the sections located in memory FLASH to SRAM1 */
    .bootloader : {
		*(.bootloader)
	} > FLASH

    /* Text section for the executed code saved in FLASH memory */
    .text :
    {
        _text_start = .;
        *(.text)               /* All the text section  (The * is for recognize all the sections that match with .text ) */
        _text_end = .;
    } > SRAM1 AT > FLASH       /* The text section is located and executed in SRAM1 but is copy to FLASH at compilation */

    /* Read only data section for the constants saved in FLASH memory */
    .rodata :
    {
        _rodata_start = .;
        *(.rodata)             /* All the read only data */
        _rodata_end = .;
    } > FLASH

    /* Data section for the initialized variables */
    .data : 
    {
        _data_start = .;
        *(.data)               /* All the data section */
        _data_end = .;
    } > SRAM1 AT > FLASH       /* The data section is located and executed in SRAM1 but is copy to FLASH at compilation */

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