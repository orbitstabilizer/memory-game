#include "icoc.h"
#include "uart.h"
#include "game_logic.h"
#include "interrupt.h"
#include "adc.h"



void setup() {
	//__enable_irq();
	GPIO_initialization();
	setup_IC();
	setup_OC();
	setup_adc();
	LPUART1_initialization();

}

int main(){

	setup();

	reset_game();

	while(1){
		__WFI;

	}
}
