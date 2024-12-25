/*
 * exti.c
 *
 *  Created on: Dec 25, 2024
 *      Author: yusufakin
 */

#include "exti.h"
#include "addresses.h"
#include "gpio.h"


void setup_exti(){

	RCC_AHB2ENR |= 0b100;     // enable GPIOC

	__BFI(GPIOC->MODER, 0b00, 8*2, 2)

	ISER0          |= 1<<19;     // enable EXTI8 interrupts

	__BFI(EXTI_EXTICR3,0x02, 0, 8 ) // select Port C as interrupt source
	EXTI_RTSR1     |= 1<<8;     // select PC8 interrupt trigger as rising edge
	EXTI_IMR1      |= 1<<8;   // unmask EXTI8 interrupt
}

