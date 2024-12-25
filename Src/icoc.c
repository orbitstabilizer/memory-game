/*
 * icoc.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Yusuf AKIN
 */


#include "icoc.h"
#include "move.h"
#include "addresses.h"


/*
 * Setup PA6 for IC using TIM16
 */
void setup_IC(){
	RCC_AHB2ENR |= (1<<('A'-'A')); // enable Port A clock

	// set PA6 to alternate mode
	__BFI(GPIOA->MODER, GPIO_MODE_ALTERNATE, 6*2, 2)

	// set PA6 alternate function to TIM16_CH1
	__BFI(GPIOA->AFRL, 14, 6*4, 4)

	// connect TIM16 clock
	RCC_APB2ENR  |= 1<<17;

	TIM16->PSC = 39999; // 0.1kHz
	TIM16->ARR = 49; // increment 0.5 second for faster game play


	// Set CH1 to input capture
	__BFI(TIM16->CCMR1, 0b01, 0, 2)

	// set filter precsclaer to 4
	TIM16->CCMR1 |= 0xb10 << 2;

	// set capture filter to f_DTS/32 with 8 samples
	TIM16->CCMR1 |= 0xF << 4;

	// enable IC
	TIM16->CCER |=1 ;

	// set trigger to both rising and falling edges
	TIM16->CCER |= ( 1<<3 | 1<<1);

	// enable IC and UI interrupts
	TIM16->DIER |=0b11;

	// clear status register
	TIM16->SR = 0;


	TIM16->CR1 |=1; // enable TIM16 clock
	ISER2 |= 1 << 6;
}


/*
 * Setup PA7 for OC using TIM17
 */
void setup_OC(){
	RCC_AHB2ENR |= 1; // PORT A clock is enabled


	// set GPIO mode to alternate
	__BFI(GPIOA->MODER, GPIO_MODE_ALTERNATE, 7*2, 2)

	// set GPIO alternate function to TIM17_CH1
	__BFI(GPIOA->AFRL, 14, 7*4, 4)


	RCC_APB2ENR |= 1 << 18; // TIM17 clock is enabled

	TIM17->BDTR |= 1 << 15; //MOE

	// select OC
	__BFI(TIM17->CCMR1, 0b00, 0, 2)


	// set output mode PWM1
	__BFI(TIM17->CCMR1, 0b0110, 4, 4)


	// default polarity is active high

	// enable the timer
	TIM17->CCER |=1 ;

	TIM17->DIER |= 0b10; // enable OC interrupt
	ISER2 |= 1 << 7; // unmask TIM17 interrupts


}

/*
 * Keeps tune player context
 */
typedef struct {
	int note_duration;
	int _is_melody;

	MOVE * _moves;
	uint32_t _melody_iter;
	uint32_t _melody_len;
	int _silence;


}_TunePlayerContext;

_TunePlayerContext _tune_player = {0};
void TIM17_IRQHandler() {
	if ((TIM17->SR & (1 << 1)) != 0) { // if OC interrupt
		TIM17->SR &= ~(1 << 1); // clear the interrupt flag
		_tune_player.note_duration--; // down counting for tone duration
		if (_tune_player.note_duration < 0){ // if target duration is reached
			if (_tune_player._is_melody && _tune_player._melody_iter+1 <_tune_player._melody_len ){
				if (!_tune_player._silence){
					_tune_player._melody_iter+=1;
					// set output mode PWM1
					__BFI(TIM17->CCMR1, 0b0110, 4, 4)
				}
				else{
					// set output mode Forced low
					__BFI(TIM17->CCMR1, 0b0100, 4, 4)
				}
				_tune_player._silence^=1;
				play_tune(
                    _tune_player._moves[ _tune_player._melody_iter].button %7, 
                    (_tune_player._moves[ _tune_player._melody_iter].time + 1) * 180
                );

			}
			else{
				TIM17->CR1 &= ~1; // stop the timer clock ( play_tune starts it)
			}
		}
	}
}



/*
 * Plays a tune for given duration (in ms)
 */
void play_tune(unsigned char note, uint16_t duration_ms){

	note %=7;
	const static int tunes[] = {
			262, 294, 330, 349, 392, 440, 494
		 //  C    D    E    F    G    A    B
	};
	int freq = tunes[note];

	int prescaler = 4000000/freq /2; // pre-calculate pre-scaler as integer, for precision
	_tune_player.note_duration =  (freq*duration_ms)/1000; // set tune duration
	TIM17->PSC = prescaler-1; // counter clock freq is set to note frequency

	// %50 percent duty cycle
	TIM17->ARR  = 1;
	TIM17->CCR1 = 1;

	// enable TIM17 clock
	TIM17->CR1 |= 1;

}

void play_melody_from_moves(MOVE* moves, uint32_t len){
	_tune_player._melody_iter = 0;
	_tune_player._moves = moves;
	_tune_player._melody_len = len;
	_tune_player._silence = 1;

	_tune_player._is_melody = 1;
	play_tune(moves->button %7, 80*( 1 + moves->time ));
}


