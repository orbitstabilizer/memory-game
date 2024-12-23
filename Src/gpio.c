

#include <stdint.h>
#include "gpio.h"
#include "addresses.h"
#include "time.h"

uint32_t display_values[10] = {
	   // ecfdgab
		0b1111011,
		0b0100001,
		0b1001111,
		0b0101111,
		0b0110101,
		0b0111110,
		0b1111110,
		0b0100011,
		0b1111111,
		0b0111111
};


Display display = {0};

void setup_gpio(){
	RCC_AHB2ENR |= (0b110011);
	GPIOA->MODER &= ~(0b101010);
	GPIOA->MODER |= (0b101010);
	GPIOB->MODER &= ~(0b1010 << (2 * 10));
	GPIOB->MODER |= (0b0101 << (2 * 10));
	GPIOE->MODER &= ~(0b10101010101010 << (2 * 7));
	GPIOE->MODER |= (0b01010101010101 << (2 * 7));
	GPIOE->MODER &= ~(0b10 << (2 * 15));
	GPIOE->MODER |= (0b01 << (2 * 15));
	GPIOF->MODER &= ~(0b101010 << (2 * 13));
	GPIOF->MODER |= (0b010101 << (2 * 13));
	GPIOF->ODR |= (0b111 << 13);
	GPIOA->ODR |= (0b111);

	RCC_APB1ENR1 |= 1 << 5;
	TIM7->PSC = 399;
	TIM7->ARR = 1;
	TIM7->CR1 &= ~(1<<1);
	TIM7->DIER |= 1;
	ISER1 |= 1 << 18;
	TIM7->CR1 |= 1;
}


void TIM7_IRQHandler(void)
{
	static uint8_t previous_turn_indicator = 3;
	static uint8_t previous_button_indicator = 8;
	TIM7->SR=0;
	GPIOE->ODR |= (1 << 15);
	GPIOB->ODR |= (0b11 << 10);
	GPIOE->ODR |= (0b1111111 << 7);
	display.current_display++;
	uint32_t number = 0 ;
	if(display.current_display == 3) display.current_display = 0;
	if(display.current_display == 0) {
		GPIOB->ODR &= ~(1 << 11);
		number = display.turn_counter / 10;
	}
	else if(display.current_display == 1) {
		GPIOB->ODR &= ~(1 << 10);
		number = display.turn_counter % 10;
	}
	else if(display.current_display == 2) {
		GPIOE->ODR &= ~(1 << 15);
		number = display.timer;
	}
	GPIOE->ODR |= (0b1111111 << 7);
	GPIOE->ODR &= ~(display_values[number] << 7);

	if(display.turn_indicator != previous_turn_indicator){
		previous_turn_indicator = display.turn_indicator;
		GPIOF->ODR |= (0b111 << 13);
		switch(display.turn_indicator){
			case 0:
				GPIOF->ODR &= ~(0b001 << 13);
				break;
			case 1:
				GPIOF->ODR &= ~(0b100 << 13);
				break;
			case 2:
				GPIOF->ODR &= ~(0b010 << 13);
				break;
			default:
				break;
		}
	}
	if(display.button_indicator != previous_button_indicator){
		previous_button_indicator = display.button_indicator;
		GPIOA->ODR |= (0b111);
		if(display.button_indicator <= 7 && display.button_indicator >=0)
			GPIOA->ODR &= ~(display.button_indicator);
	}

}
