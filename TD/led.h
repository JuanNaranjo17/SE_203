#ifndef LED_H
#define LED_H

#include <stm32l4xx.h>
#include <stdint.h>

// Enum for represent the LEDs state
typedef enum {
    LED_OFF,
    LED_YELLOW,
    LED_BLUE
} led_state_t;

//Functions instance
void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(led_state_t state);
void switch_LED_g(void);
void test_LED(void);
void delay(void);

#endif