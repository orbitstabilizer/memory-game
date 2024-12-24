#include "exti.h"
#include "game_logic.h"

void setup_exti(){ 

    RCC_AHB2ENR |= 0b1 << 0; // The clock for GPIO Port A
	GPIOA->MODER &= ~(0b11 << (6 * 2));// //PA6 input switches
	GPIOA->PUPDR &= ~(0b10 << (6 * 2));// internal pull down PA6

    //EXTI->RTSR1 |= (0b1 << 6); //PA6
    EXTI->FTSR1 |= (0b1 << 6); //PA6
    EXTI->IMR1 |= (0b1<<6); //PA6
    ISER0 |= (0b1 << 17); //enable EXTI6 interrupts
}

void disable_exti(){
    EXTI->IMR1 &= ~(0b1<<6); //PA6
    ICER0 &= ~(0b1 << 17);
}




