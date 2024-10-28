#include "matrix.h"

// Aproximate Solution
void delay_ms(int ms){
    for (int i = 0; i < ms*80000000/1000; i++)                                              // Clock frequency * time = number of pass instructions
        asm volatile("nop");
}

void matrix_init()
{
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);      // Enable the port A, B and C clock

    // Define PORTx IO as OUTPUT (Assign the relevant pins as digital outputs)
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_1 | GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1 | GPIO_MODER_MODE15_1);
    GPIOA->MODER |=  (GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE15_0);
    GPIOB->MODER &= ~(GPIO_MODER_MODE0_1 | GPIO_MODER_MODE1_1 | GPIO_MODER_MODE2_1);
    GPIOB->MODER |=  (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0);
    GPIOC->MODER &= ~(GPIO_MODER_MODE3_1 | GPIO_MODER_MODE4_1 | GPIO_MODER_MODE5_1);
    GPIOC->MODER |=  (GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0);

    // Define the OUTPUTS as very-high-speed
    GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED2 | GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5 | GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7 | GPIO_OSPEEDR_OSPEED15);
    GPIOB->OSPEEDR |= (GPIO_OSPEEDR_OSPEED0 | GPIO_OSPEEDR_OSPEED1 | GPIO_OSPEEDR_OSPEED2);
    GPIOC->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED4 | GPIO_OSPEEDR_OSPEED5);

    // Output initialization
    RST(0);
    LAT(1);
    SB(1);
    SCK(0);
    SDA(0);
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);

    // Wait 100 ms to wait the DM163 being initialized.
    delay_ms(100);
    RST(1);

    // Init BANK0 for be able to use the register bank1 and obtain more color representations
    init_bank0();

    // Stablish the BANK1 as default
    SB(1);
}

void pulse_SCK(){               // delay > 25 ns = 0.000025 ms
    SCK(0);
    delay_ms(0.000025);
    SCK(1);
    delay_ms(0.000025);
    SCK(0);
}

void pulse_LAT(){               // delay > 25 ns = 0.000025 ms for high state, delay > 7 ns = 0.00007 ms for low state
    LAT(1);
    delay_ms(0.000025);
    LAT(0);
    delay_ms(0.000025);
    LAT(1);
}


void deactivate_rows()
{
    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row){
    switch (row) {
        case 0:
            ROW0(1);
            break;
        case 1:
            ROW1(1);
            break;
        case 2:
            ROW2(1);
            break;
        case 3:
            ROW3(1);
            break;
        case 4:
            ROW4(1);
            break;
        case 5:
            ROW5(1);
            break;
        case 6:
            ROW6(1);
            break;
        case 7:
            ROW7(1);
            break;
        default:
            // Error handle
            break;
    }

}

void send_byte(uint8_t val){
    for (uint8_t i = 8; i > 0; i--) {           // Send 8 bits since the most significant bit till the less significant bit
        SDA(val & (1 << (i - 1)));              // Obtain the bit in the i position and send it using SDA
        pulse_SCK();                            // Pulse for register the bit
    }
}

void mat_set_row(int row, const rgb_color *val)
{
    if (row < 0 || row > 7) return;                 // Invalid row handle
    for (uint8_t i = 8; i > 0; i--){                // Send the RGB row color since left to rigth
        send_byte(val[i - 1].b);                    // Send the blue component
        send_byte(val[i - 1].g);                    // Send the green component
        send_byte(val[i - 1].r);                    // Send the red component
    }
    deactivate_rows();                              // Desactivate all the rows
    pulse_LAT();                                    // Upload the DM163 outputs
    activate_row(row);                              // Activate the row selected
}

void init_bank0(){
    SB(0);                                          // Select BANK0
    for (uint8_t i = 0; i < 144; i++) {
        SDA(1);                                     // Send a 1 144 times for fill out the register BANK0 for become available the BANK1 use
        pulse_SCK();                                // Register the bit
    }
    pulse_LAT();                                    // Upload the register BANK0
}

void test_pixels(){
    rgb_color color[8];                             // 8 LED's structure
    for (uint8_t i = 0; i < 8; i++){                // Upload each color LED in a row
        color[i].r = 0;
        color[i].g = 0;
        color[i].b = ((256 / (i + 1)) - 1);         // Blue's intensity
    }
    for (uint8_t i = 0; i < 8; i++){                // Iterate the row
        mat_set_row(i, color);                      // Send the row
        delay_ms(10);                               // Wait 10ms
    }
    for (uint8_t i = 0; i < 8; i++){
        color[i].r = 0;
        color[i].g = ((256 / (i + 1)) - 1);         // Green's intensity
        color[i].b = 0;
    }
    for (uint8_t i = 0; i < 8; i++){
        mat_set_row(i, color);
        delay_ms(10);
    }
    for (uint8_t i = 0; i < 8; i++){
        color[i].r = ((256 / (i + 1)) - 1);         // Red's intensity
        color[i].g = 0;
        color[i].b = 0;
    }
    for (uint8_t i = 0; i < 8; i++){
        mat_set_row(i, color);
        delay_ms(10);
    }
}

void test_image(){
    const uint8_t *byte_start = &_binary_image_raw_start;       // Obtain the first byte of the image.o using the symbole given by the makefile
    rgb_color LED[8];                                           // Instance of a row

    while(1){                                                   // Keep showing the image
        for (uint8_t row = 0; row < 8; row++) {                 // Go through the rows
            for (uint8_t i = 0; i < 8; i++) {                   // Set each LED in a row with the correspondent value
                LED[i].r = *byte_start++;
                LED[i].g = *byte_start++;
                LED[i].b = *byte_start++;
            }
            mat_set_row(row, LED);                              // Put the row value in the DM163
        }
        byte_start -= 192;                                      // Recover the init address
    }
}
