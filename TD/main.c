#include "led.h"            // Include the library for handle the LED
#include "clocks.h"         // Include the library for handle the clocks
#include "uart.h"           // Include the library for handle the USART
#include "matrix.h"         // Include the library for handle the LED matrix
#include "irq.h"            // Include the library for handle the interruptions
#include "buttons.h"        // Include the library for handle the buttons interruptions

void delay(){
    for (int i = 0; i < 10000; i++) {
            asm volatile("nop"); // Delay
        }
}

int fibo(int n) {
    if (n <= 0) {
        return 0;  // F(0) = 0
    } else if (n == 1) {
        return 1;  // F(1) = 1
    } else {
        return fibo(n - 1) + fibo(n - 2);  // Recursive function
    }
}


int main(){
    led_init();
    matrix_init();
    irq_init();
    button_init();
    test_image();

    while (1);
    return 0;
}
