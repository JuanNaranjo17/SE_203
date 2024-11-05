#include "uart.h"

static volatile uint8_t frame_index = 0;
volatile uint8_t frame_ready = 0;
volatile uint8_t frames[192];

void uart_init(int baudrate){

    // Disable the USART for handle the setup
    USART1->CR1 &= ~(USART_CR1_UE);

    // Enable the port B clock
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN);

    // Put the pin TX and RX in the alternate function mode
    GPIOB->MODER |= (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);                                                         // Set PB6 and PB7 in alternate function mode, TX and RX respectively
    GPIOB->MODER &= ~(GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);
    GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk);                                                   // Clean the AFRL[0] register
    GPIOB->AFR[0] |= (7 << GPIO_AFRL_AFSEL6_Pos);                                                                      // Set the alternate function to TX
    GPIOB->AFR[0] |= (7 << GPIO_AFRL_AFSEL7_Pos);                                                                      // Set the alternate function to RX

    // Enable the USART clock
    RCC->APB2ENR |= (RCC_APB2ENR_USART1EN);
    
    // Select PCLK as the clock for the port USART1 (00)
    RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL);

    // Reset the USART1
    RCC->APB2RSTR |= (RCC_APB2RSTR_USART1RST);
    RCC->APB2RSTR &= ~(RCC_APB2RSTR_USART1RST);             // Turn off the reset

    // Set up mode 8N1, 8 databits, no parity bit, 1 stop bit, 115200 bps
    USART1->BRR = (uint32_t) (FreqSysClk / baudrate);       // Set 115200 bps
    // Setup the 8N1 mode
    USART1->CR1 &= ~(USART_CR1_OVER8);                      // Oversampling by 16
    USART1->CR1 &= ~(USART_CR1_M);                          // 1 Start bit, 8 data bits, n stop bits
    USART1->CR1 &= ~(USART_CR1_PCE);                        // Parity control disabled
    USART1->CR2 &= ~(USART_CR2_STOP);                       // 1 stop bit

    // Enable the USART, the transmition and reception
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

    USART1->CR1 |= USART_CR1_RXNEIE;                        // RXNE interrupt enable, a USART interruption generated when RXNE = 1 or ORE = 1

    // Enable USART1 interruption handler
    NVIC_EnableIRQ(USART1_IRQn);

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

void test_USART(){
    char buffer[12];
    uart_putchar('H');
    while(1){
        uint8_t c = uart_getchar();     // Receive a character
        uart_putchar(c);                // Send the character
        uart_puts("cachon");
        uart_gets(buffer, 12);
        uart_puts("You wrote: ");
        uart_puts(buffer);
        uart_putchar('\n');             // Add a newline character for improve the format
        uart_puts("cachon");

    }
}

void USART1_IRQHandler(void){
    if (USART1->ISR & USART_ISR_RXNE){                      // Check if exists received data
        uint8_t byte_received = uart_getchar();             // Read the received data

        if (byte_received == 0xFF){
            frame_index = 0;
        }else{
            frames[frame_index] = byte_received;
            frame_index++;
        }
    }
}

// JLinkExe -device STM32L475VG -if SWD -autoconnect 1 -speed auto ...
// make connect
// tio /dev/ttyACM0 -b 115200 -d 8 --parity none --stopbits 1 -f none
// arm-none-eabi-gdb main
// target extended-remote :2331
// load
// continue 