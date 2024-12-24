#include "exti.h"

void setup_exti(){ 

    RCC_AHB2ENR |= 0b1 << 0; // The clock for GPIO Port A
	GPIOA->MODER &= ~(0b11 << (5 * 2));// //PA5 input switches
	GPIOA->PUPDR &= ~(0b10 << (5 * 2));// internal pull down PA5

    //EXTI->RTSR1 |= (0b1 << 5); //PA5
    EXTI->FTSR1 |= (0b1 << 5); //PA5
    EXTI->IMR1 |= (0b1<<5); //PA5
    ISER0 |= (0b1 << 16); //enable EXTI5 interrupts
}

void disable_exti(){
    EXTI->IMR1 &= ~(0b1<<5); //PA5
    ICER0 |= (0b1 << 16);
}




