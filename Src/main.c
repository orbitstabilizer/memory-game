#include "icoc.h"
#include "uart.h"
#include "gpio.h"
#include "game_logic.h"
#include "interrupt.h"
#include "adc.h"
#include "exti.h"



void setup() {
	__enable_irq();
	setup_exti();
	setup_gpio();
	setup_IC();
	setup_OC();
	setup_adc();
	LPUART1_initialization();
	reset_game();


}

int main(){
	setup_saz_mix();
	setup();



	while(1){
		__WFI;

	}
}


