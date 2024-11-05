.syntax unified
.arch armv7-m
.cpu cortex-m4
.global _start
.global _exit
.thumb

.thumb_func

_start:
    ldr sp, = _stack_start  @ Inicializa el puntero de pila
    bl init_bss             @ Inicializa el BSS
    bl main                 @ Llama a main
_exit:
    b _exit                 @ Bucle infinito
