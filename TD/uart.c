#include "uart.h"

uint32_t FreqSysClk = 80000000;

void uart_init(){

    // Disable the USART for handle the setup
    USART1->CR1 &= ~(USART_CR1_UE);

    // Enable the port B and USART clock
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_APB2ENR_USART1EN);

    // Put the pin TX and RX in the alternate function mode
    GPIOB->MODER &= ~(GPIO_MODER_MODE6_Msk | GPIO_MODER_MODE7_Msk);                                                    // Clean PB6 and PB7 bits
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);                                                         // Set PB6 and PB7 in alternate function mode, TX and RX respectively
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);                                                   // Clean the AFRL[0] register
    GPIOB->AFR[0] |= (7 << GPIO_AFRL_AFSEL6_Pos);                                                                      // Set the alternate function to TX
    GPIOB->AFR[0] |= (7 << GPIO_AFRL_AFSEL7_Pos);                                                                      // Set the alternate function to RX

    // Select PCLK as the clock for the port USART1 (00)
    RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL);

    RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST);
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);             // Turn off the reset

    // Set up mode 8N1, 8 databits, no parity bit, 1 stop bit, 115200 bps
    USART1->BRR = ((FreqSysClk) / 115200);                  // Set 115200 bps
    // Clean the register CR1 and CR2
    USART1->CR1 &= ~(USART_CR1_OVER8);                      // Clean register over8
    USART1->CR1 &= ~(USART_CR1_M);                          // Clean the register M
    USART1->CR1 &= ~(USART_CR1_PCE);                        // Clean the register PCE
    USART1->CR2 &= ~(USART_CR2_STOP);                       // Clean the register STOP
    // Setup the 8N1 mode
    USART1->CR1 &= ~(USART_CR1_OVER8 | USART_CR1_M | USART_CR1_PCE);
    USART1->CR2 &= ~(USART_CR2_STOP);

    // Enable the USART, the transmition and reception
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);
}
// Send a character
// TDR = Transmitter data register  (Stored the value for send)
// TXE = Transmitter data register empty. Is a flag
// ISR = Interrupt Status Register
void uart_putchar(uint8_t c){
    // Wait until the transmisor be ready
    while (!(USART1->ISR & USART_ISR_TXE)); // Wait until the register TDR be empty  (When TXE = 1, there is not a current transmision and TDR has not a value)
    USART1->TDR = c;                        // Send the caracter
}
// Receive a character
// RXNE = Receive Not Empty, is a flag.
// RDR = Receiver data register
// FE = Framig error flag
// ORE = Overrun error flag
uint8_t uart_getchar(){
    // Wait until a character is received
    while (!(USART1->ISR & USART_ISR_RXNE)); // Wait until the register RDR be full
    // Check if there is a framing or overrun error
    if (USART1->ISR & (USART_ISR_FE | USART_ISR_ORE)){
        // Handle error routine
        while (1); // Error: Infinite loop
        return 0;
    }
    return USART1->RDR; // Return the receive character

}
// Send a sting
void uart_puts(const char *s){
    while (*s) {                        // While is not the string end (The C convention says that all string ends with a null character)
        uart_putchar((uint8_t)*s);      // Send the character
        s++;
    }
    uart_putchar((uint8_t)'\r');        // Car return
    uart_putchar((uint8_t)'\n');        // NewLine character
}
// Receive a string
void uart_gets(char *s, size_t size){
    size_t i = 0;
    while ((i < size) && (s[i] != '\n')) {                  // Write until end or when find a newline character
        s[i] = (char) uart_getchar();                       // Receive a character
        if (USART1->ISR & (USART_ISR_FE | USART_ISR_ORE)){  // Check if there is a framing or overrun error
            while (1);
        }
        i++;
    }
    s[i] = '\0';                                            // Add the end null character to the String

}
// checksum
/*void checksum(){
    uint32_t checksum_var = 0;  
    while (1) {
        uint8_t byte = uart_getchar();
        checksum_var += byte;
        //uart_putchar(byte);
    }
}*/
void checksum() {
    uint32_t checksum_var = 0;
    char buffer[9];                                     // Buffer to store the hexadecimal representation(8 bits + null terminator)
    const char hex_chars[] = "0123456789ABCDEF";

    // Receive 1000 bytes
    for (int i = 0; i < 1000; i++) {
        uint8_t byte = uart_getchar();
        checksum_var += byte;
    }

    // Convert checksum_var to hexadecimal
    for (int i = 7; i >= 0; i--) {
        buffer[i] = hex_chars[checksum_var & 0xF];      // Take the last 4 bits and convert to hexadecimal
        checksum_var >>= 4;                             // Shift 4 bits to right
    }
    buffer[8] = '\0';                                   // Null terminator for finish the string

    // Show the sum
    uart_puts(buffer);
}
// JLinkExe -device STM32L475VG -if SWD -autoconnect 1 -speed auto ...
// make connect
// tio /dev/ttyACM0 -b 115200 -d 8 --parity none --stopbits 1 -f none
// arm-none-eabi-gdb main
// target extended-remote :2331
// load
// continue 