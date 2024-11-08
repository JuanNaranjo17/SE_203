#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <stm32l4xx.h>
#include "frequency.h"
#include "irq.h"
#include "led.h"

void timer_init(int max_us);

#endif