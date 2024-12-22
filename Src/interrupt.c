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
			TIM16->CNT=0; // reset timer counter
			ic.increment=1; // set increment so that the time context variable keeps pulse duration
			ic.time=0; // reset time context
			ADC_1->CR |= (1 << 2); //Start regular conversion of ADC
			ic_on_progress = 1;
		}
		else{
			/*
			 * PUBLISH NOTE TIME WITH UART
			 */
			if (current_turn != OPPONENT) {
				if (button_pressed != -1) {
					handle_player_turn((MOVE){0, ic.time%5, false});
					button_pressed = -1;
				}
				play_tune(ic.time%7, 100);
			}
			ic_on_progress = 0;
			ic.increment=0;
		}
	}

	// On timer update event increment context time
	if ((TIM16->SR & 1) != 0){
		ic.time+=ic.increment; // increment time only if measuing the pulse
		if (ic.time > 9) ic.time = 0;
		TIM16->SR &= ~1;
	}

	// display current time
	// write_to_7s(self.time);

}

void ADC1_2_IRQHandler() {

	if ((ADC_1->ISR & 1 << 2) != 0) { //Check EOC

		uint32_t temp = ADC_1->DR;
		uint8_t result = temp * 33 / 4095;
		uint16_t voltage = result;
		button_pressed = get_button(voltage);

		if (ic_on_progress == 0) {
			handle_player_turn((MOVE){0, ic.time%5, false});
		}

	}

	return;

}


void __enable_irq(void) {
    __asm volatile(
        "mov r0, #0 \n\t"
        "msr primask, r0 \n\t"
    );
}
