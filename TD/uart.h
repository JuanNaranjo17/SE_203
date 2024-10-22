#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>
#include <stm32l4xx.h>

extern uint32_t FreqSysClk;                                                                                  // Set the micro clock

void uart_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
void checksum();

#endif