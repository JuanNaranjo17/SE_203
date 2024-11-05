#include "led.h"

void led_init(){

    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);   // Turn on the clock for the port B and C

    // Set the pin 14 of port B as digital output
    GPIOB->MODER &= ~(GPIO_MODER_MODE14_1);
    GPIOB->MODER |= GPIO_MODER_MODE14_0;
    GPIOC->MODER &= ~GPIO_MODER_MODE9;                             // Set PC9 temporarly as input, then the led is turned off

}

void led_g_on(){
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);                           // Set the pin 14 high
}

void led_g_off(){
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);                           // Set the pin 14 low
}

void led(led_state_t state) {
    switch(state) {
        case LED_YELLOW:
            // Setup PC9 as output and put it high
            GPIOC->BSRR = GPIO_BSRR_BS9;
            GPIOC->MODER &= ~(GPIO_MODER_MODE9_1);                                       // Setup the mode 9 as digital output
            GPIOC->MODER |= GPIO_MODER_MODE9_0;
            break;
        case LED_BLUE:
            // Setup PC9 as output and put it low
            GPIOC->BSRR = GPIO_BSRR_BR9;                                                 // Set PC9 low
            GPIOC->MODER &= ~(GPIO_MODER_MODE9_1);                                       // Setup the mode 9 as digital output
            GPIOC->MODER |= GPIO_MODER_MODE9_0;
            break;
        default:
            GPIOC->MODER &= ~(GPIO_MODER_MODE9);                                         // PC9 as input
            break;
    }
}

void switch_LED_g(){

    if (GPIOB->ODR & GPIO_ODR_OD14) led_g_off();                                        // Read the output data register, if 1, turn off the LED, otherwise turn on
    else led_g_on();
}

void delay(){
    for (uint32_t i = 0; i < 1000000; i++) {
            asm volatile("nop"); // Delay
        }
}

void test_LED(){
    while(1){
        led_g_on();         // Turn on the green LED
        delay();
        led_g_off();        // Turn off the green LED
        led(LED_YELLOW);    // Turn on the yellow LED
        delay();
        led(LED_BLUE);      // Turn on the blue LED
        delay();
        led(LED_OFF);       // Turn on the LED
    }
}