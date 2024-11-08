#include "frequency.h"

const uint32_t FreqSysClk = 80000000;           // Set the microcontroller clock
volatile uint8_t update_is_able = 0;            // Initialize the flag for the matrix update