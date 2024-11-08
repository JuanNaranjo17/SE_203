#include "timer.h"

void timer_init(int max_us){
    // Activate the TMI2 clock
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // Clean the status flags in TIM2_SR
    TIM2->SR = 0x0000;                          // Reset value

    // Set the counter in zero
    TIM2->CNT = 0x00000000;

    // Setup the timer 2
    // Without clock divider, Edge aligned mode (Counter count up or down depending the direction DIR, Direction set up as upcounter, One Pulse Mode (Counter not stopped at update event))
    TIM2->CR1 &= ~(TIM_CR1_CKD | TIM_CR1_CMS | TIM_CR1_DIR | TIM_CR1_OPM);

    // Set the TIM2 preescaler for count each microsecond
    TIM2->PSC = (uint32_t) (80000000/1000000) - 1 ;

    // Define the duration time to be counted
    TIM2->ARR = max_us;

    // Upload interrupt enable TIM2
    TIM2->DIER |= TIM_DIER_UIE;                 // Update Interrupt Enable enabled (DMA/Interrupt Enable Register)

    // Activate the TIM2 interruption
    NVIC_EnableIRQ(TIM2_IRQn);

    // Activate the TIM2
    TIM2->CR1 |= TIM_CR1_CEN;                   // Timer 2 control register 1 counter enable set as 1

}

void TIM2_IRQHandler(){

    if (TIM2->SR & TIM_SR_UIF) {                // Check if Update interrupt flag is 1, 1 if an update interrupt pending. Cleared by software 
        TIM2->SR &= ~TIM_SR_UIF;                // Clean the flag
        //switch_LED_g();                         // Switch the green LED
        update_is_able = 1;                     // Update the flag
    }
}