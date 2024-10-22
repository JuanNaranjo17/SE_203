#include <stdint.h>         // Library for handle int
#include <stdbool.h>        // Library for use the boolean
#include "led.h"            // Include the library for handle the LED
#include "clocks.h"         // Include the library for handle the clocks
#include "uart.h"           // Include the library for handle the USART

/*
int i;
int a;
int c;
int h;
*/

/*int fibo(int n) {
    if (n <= 0) {
        return 0;  // F(0) = 0
    } else if (n == 1) {
        return 1;  // F(1) = 1
    } else {
        return fibo(n - 1) + fibo(n - 2);  // Recursive function
    }
}*/

void delay(){
    for (int i = 0; i < 10000; i++) {
            asm volatile("nop"); // Delay
        }
}

int main(){
    //while (true);
    
    //return fibo(8);
    //clocks_init();
    //led_init();
    uart_init();
    //char buffer[12];

    while (1) {
        /*
        led_g_on();         // Turn on the green LED
        delay();
        led_g_off();        // Turn off the green LED
        led(LED_YELLOW);    // Turn on the yellow LED
        delay();
        led(LED_BLUE);      // Turn on the blue LED
        delay();
        led(LED_OFF);       // Turn on the LED
        */
        //uart_putchar('H');
        //led_g_on();
        /*uint8_t c = uart_getchar();     // Receive a character
        uart_putchar(c);                // Send the character
        uart_puts("cachon");
        uart_gets(buffer, 12);
        uart_puts("You wrote: ");
        uart_puts(buffer);
        uart_putchar('\n');             // Add a newline character for improve the format
        uart_puts("cachon");*/
        checksum();
    }
    return 0;
}
