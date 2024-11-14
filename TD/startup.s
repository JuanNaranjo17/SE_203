.syntax unified
.arch armv7-m
.cpu cortex-m4
.global _start
.global _exit
.thumb


.section .bootloader, "ax", %progbits       @ Define the content of bootloader section, this is the code executed since FLASH for copy the sections in RAM.

.thumb_func

_start:
    ldr sp, = _stack_start  @ Initialize the stack pointer
    bl init_text            @ Initialize the text section in SRAM1 memory since FLASH
    bl init_isr             @ Initialize the isr_vector in SRAM1 memory since FLASH
    bl init_data            @ Initialize the data section in SRAM1 memory since FLASH 
    bl init_bss             @ Initialize BSS section in SRAM1 memory
    bl main                 @ Call main
_exit:
    b _exit                 @ Infinite loop
