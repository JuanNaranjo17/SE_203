.syntax unified
.global _start
.thumb

.section .text

_start:
    // Initialiser la pile et les segments de mémoire si nécessaire

    bl main           // Call the main function
    bx lr             // back since the function main

_exit:
    b _exit