#ifndef UART_H
#define UART_H

#include <stdint.h>
#include <stddef.h>
#include <stm32l4xx.h>
#include "frequency.h"
#include "irq.h"

extern volatile uint8_t frames[192];                                                                         // Set the frame size
extern volatile uint8_t frame_ready;                                                                         // Set if the frame is totally received

void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);
void checksum();
void test_USART(void);

#endif