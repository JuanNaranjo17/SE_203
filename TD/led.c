#include "led.h"
#include <stdint.h>

#define GPIOB_BASE          0x48000400
#define GPIOC_BASE          0x48000800

#define GPIOB_MODER         (*(volatile uint32_t *) (GPIOB_BASE + 0x0))
#define GPIOB_BSRR          (*(volatile uint32_t *) (GPIOB_BASE + 0x18))

#define GPIOC_MODER         (*(volatile uint32_t *) (GPIOC_BASE + 0x0))
#define GPIOC_BSRR          (*(volatile uint32_t *) (GPIOC_BASE + 0x18))

#define RCC_BASE            0x40021000
#define RCC_AHB2ENR         (*(volatile uint32_t *) (RCC_BASE + 0x4c))

void led_init(){

    RCC_AHB2ENR |= (1 << 1);                  // Turn on the clock for the port B
    RCC_AHB2ENR |= (1 << 2);                  // Turn on the clock for the port C

    // Set the pin 14 of port B as digital output
    GPIOB_MODER &= ~(0b11 << 28);           // Clean the mode 14 bits (Put it in 0)
    GPIOB_MODER |= (0b01 << 28);            // Set the mode 14 as digital output

    GPIOC_MODER &= ~(0b11 << 18);           // Set PC9 temporarly as input, then the led is turned off

}

void led_g_on(){
    GPIOB_BSRR = (1 << 14);                 // Set the pin 14 high
}

void led_g_off(){
    GPIOB_BSRR = (1 << (14 + 16));          // Set the pin 14 low
}

void led(led_state_t state) {
    switch(state) {
        case LED_OFF:
            // Set up PCP as input (High impedance)
            GPIOC_MODER &= ~(0b11 << 18);   // PC9 as input
            break;
        case LED_YELLOW:
            // Setup PC9 as output and put it high
            GPIOC_BSRR = (1 << 9);          // Set PC9 high
            GPIOC_MODER |= (0b01 << 18);    // Setup the mode 9 as digital output
            break;
        case LED_BLUE:
            // Setup PC9 as output and put it low
            GPIOC_BSRR = (1 << (9 + 16));   // Set PC9 low
            GPIOC_MODER |= (0b01 << 18);    // Setup the mode 9 as digital output
            break;
    }
}
