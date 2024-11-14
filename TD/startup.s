.syntax unified
.arch armv7-m
.cpu cortex-m4
.global _start
.global _exit
.thumb

.thumb_func

_start:
    ldr sp, = _stack_start  @ Initialize the stack pointer
    bl init_data            @ Initialize the data section in SRAM1 memory since FLASH
    bl init_bss             @ Initialize BSS section in SRAM1 memory
    bl main                 @ Call main
_exit:
    b _exit                 @ Infinite loop
