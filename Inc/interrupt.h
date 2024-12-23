#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "addresses.h"
#include "gpio.h"
#include "move.h"
#include "uart.h"
#include "game_logic.h"
#include "adc.h"
#include "icoc.h"

void LPUART1_IRQHandler(void);
void TIM16_IRQHandler();
void ADC1_2_IRQHandler();
void __enable_irq(void);


#endif
