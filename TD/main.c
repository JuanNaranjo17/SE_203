#include <stdint.h>         // Library for handle int
#include <stdbool.h>        // Library for use the boolean
#include "led.h"            // Include the library for handle the LED
#include "clocks.h"         // Include the library for handle the clocks
#include "uart.h"           // Include the library for handle the USART
#include "matrix.h"         // Include the library for handle the LED matrix

void delay(){
    for (int i = 0; i < 10000; i++) {
            asm volatile("nop"); // Delay
        }
}

int main(){
    matrix_init();

    while (1) {
        test_image();
    }
    return 0;
}
