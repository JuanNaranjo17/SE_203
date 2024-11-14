#include "led.h"            // Include the library for handle the LED
#include "clocks.h"         // Include the library for handle the clocks
#include "uart.h"           // Include the library for handle the USART
#include "matrix.h"         // Include the library for handle the LED matrix
#include "irq.h"            // Include the library for handle the interruptions
#include "buttons.h"        // Include the library for handle the buttons interruptions
#include "timer.h"          // Include the library for handle the timer interruptions

int fibo(int n) {
    if (n <= 0) {
        return 0;  // F(0) = 0
    } else if (n == 1) {
        return 1;  // F(1) = 1
    } else {
        return fibo(n - 1) + fibo(n - 2);  // Recursive function
    }
}


int __attribute__((section(".text"))) main(){
    clocks_init();
    led_init();
    uart_init(38400);
    matrix_init();
    irq_init();
    button_init();
    timer_init(1000000/(60*8));
    //test_USART();
    //test_LED();
    //test_pixels();


    test_image((uint8_t *)frames);
    test_image(&_binary_image_raw_start);

    while (1);
    return 0;
}
