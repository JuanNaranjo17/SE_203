#ifndef IRQ_H
#define IRQ_H

#include <stm32l4xx.h>
#include <core_cm4.h>

// Default model for the interuption subrutines, is defined weak for be able to give another function definition in another file
// Disable the interruptions for guarantee that other interuption will not interupt the actual interuption
#define MAKE_DEFAULT_HANDLER(truc_IRQHandler)                \
    void __attribute__((weak)) truc_IRQHandler(void) {       \
        __disable_irq();                                     \
        while(1);                                            \
    }
extern uint32_t _stack_start;
extern void _start(void);

// Function instance
void irq_init(void);                                              

#endif