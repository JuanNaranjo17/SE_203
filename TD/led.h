#ifndef LED_H
#define LED_H

#include <stdint.h>

// Enum for represent the LEDs state
typedef enum {
    LED_OFF,
    LED_YELLOW,
    LED_BLUE
} led_state_t;

void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(led_state_t state);

#endif