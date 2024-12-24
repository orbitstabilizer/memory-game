#include "interrupt.h"

int ic_on_progress = 0;
int button_pressed = -1;

void LPUART1_IRQHandler(void) {
    if ((LPUART1->ISR & (1 << 5)) != 0) {
    	// Read the arrived value.


        MOVE move = read_message();

		// Check if the move is valid.
		if (!move.fail && (move.button < 0 || move.button >= 7)) {
			return;
		}
		if (!move.fail && (move.time < 0 || move.time >= 5)) {
			return;
		}

		handle_opponents_turn(move);
    }
}

/*
 * Context for IC operations are keept in this struct
 */
struct _ICContext{
	uint32_t time;// in seconds
	char     increment; // 0 or 1 : used for pulse width measurement
	char     is_rising_edge; // indicates edge direction
};
struct _ICContext ic = {0};

void TIM16_IRQHandler() {
	// init internal context

	if ((TIM16->SR & (1 << 1)) != 0) { // if rising or falling edge
		TIM16->SR &= ~(1 << 1); // clear the interrupt
		ic.is_rising_edge^=1; // toggle rising/falling edge flag
		if (ic.is_rising_edge){
			/*
			 * USE ADC TO DETECT WHICH BUTTON IS PRESSED
			 */
			if (current_turn != OPPONENT) {
				TIM16->CNT=0; // reset timer counter
				ic.increment=1; // set increment so that the time context variable keeps pulse duration
				ic.time=0; // reset time context
				display.timer = ic.time;
				button_pressed = -1;
				 ADC_1->CR |= (1 << 2); //Start regular conversion of ADC
				ic_on_progress = 1;
			}


		}
		else{
			/*
			 * PUBLISH NOTE TIME WITH UART
			 */
			while(button_pressed == -1);

			if (current_turn != OPPONENT) {
				handle_player_turn((MOVE){button_pressed, ic.time%3, false});
//				if (button_pressed != -1) {
//					handle_player_turn((MOVE){0, ic.time%5, false});
//					button_pressed = -1;
//				}
				play_tune(button_pressed, 100 * ( (ic.time%3) +1));
			}
//			play_tune(ic.time%7, 100);
			ic_on_progress = 0;
			ic.increment=0;
		}
	}

	// On timer update event increment context time
	if ((TIM16->SR & 1) != 0){
		ic.time+=ic.increment; // increment time only if measuing the pulse

		if (ic.time > 3) ic.time = 0;
		TIM16->SR &= ~1;
	}

	// display current time
	display.timer = ic.time;

}

void ADC1_2_IRQHandler() {

	if ((ADC_1->ISR & 1 << 2) != 0) { //Check EOC

		uint32_t voltage = ADC_1->DR;
		button_pressed = get_button(voltage);

//		if (button_pressed != -1 && ic_on_progress == 0) {
			// handle_player_turn((MOVE){0, ic.time%5, false});
			// button_pressed = -1;
//		}

	}

	return;

}


void __enable_irq(void) {
    __asm volatile(
        "mov r0, #0 \n\t"
        "msr primask, r0 \n\t"
    );
}
