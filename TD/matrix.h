#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stddef.h>
#include <stm32l4xx.h>

// DM163 - microcontroller pin map
/*
    RST	PC3
    SB	PC5
    LAT	PC4
    SCK	PB1
    SDA	PA4
    C0	PB2
    C1	PA15
    C2	PA2
    C3	PA7
    C4	PA6
    C5	PA5
    C6	PB0
    C7	PA3
*/

#define RST(output) GPIOC->BSRR = (output ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3)      // If output is 1, select GPIO_BSRR_BS3, it means, put the pin C3 high, if output is 0, select GPIO_BSRR_BR3, it means, put the pin C3 low
#define SB(output)  GPIOC->BSRR = (output ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5)      // If output is 1, select GPIO_BSRR_BS5, it means, put the pin C5 high, if output is 0, select GPIO_BSRR_BR5, it means, put the pin C5 low
#define LAT(output) GPIOC->BSRR = (output ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4)      // If output is 1, select GPIO_BSRR_BS4, it means, put the pin C4 high, if output is 0, select GPIO_BSRR_BR4, it means, put the pin C4 low
#define SCK(output) GPIOB->BSRR = (output ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1)      // If output is 1, select GPIO_BSRR_BS1, it means, put the pin B1 high, if output is 0, select GPIO_BSRR_BR1, it means, put the pin B1 low
#define SDA(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4)      // If output is 1, select GPIO_BSRR_BS4, it means, put the pin A4 high, if output is 0, select GPIO_BSRR_BR4, it means, put the pin A4 low

#define ROW0(output) GPIOB->BSRR = (output ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2)
#define ROW1(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS15 : GPIO_BSRR_BR15)
#define ROW2(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS2 : GPIO_BSRR_BR2)
#define ROW3(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS7 : GPIO_BSRR_BR7)
#define ROW4(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS6 : GPIO_BSRR_BR6)
#define ROW5(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS5 : GPIO_BSRR_BR5)
#define ROW6(output) GPIOB->BSRR = (output ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0)
#define ROW7(output) GPIOA->BSRR = (output ? GPIO_BSRR_BS3 : GPIO_BSRR_BR3)

// Structure for define the LED's color representation
typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;

// Functions instance
void matrix_init();
void delay_ms(int ms);
void pulse_SCK();
void pulse_LAT();
void deactivate_rows();
void activate_row(int row);
void send_byte(uint8_t val);
void mat_set_row(int row, const rgb_color *val);
void init_bank0();
void test_pixels();

#endif