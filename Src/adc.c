#include "adc.h"

void setup_adc() {
    RCC_AHB2ENR |= (1<<1);
	RCC_AHB2ENR |= (1<<2);
	RCC_AHB2ENR |= (1<<13);
	RCC_CCIPR1 |= (3<<28);

    GPIOC->MODER &= ~(0b11 << (3*2));
	GPIOC->MODER |= (3 << (3*2));

	ADC_1->CR &= ~(1 << 29); //take ADC module from deep-power down
	ADC_1->CR |= (1 << 28); //turn on ADC voltage regulator



	// ADC->CCR |= (1 << 22);   // Set V_REF as external reference (typically 5V)


	ADC->CCR |= (3 << 16); //ADC_CLK = 1MHz (HCLK/4)
	ADC_1->SMPR1 |= (0b111 << 12); //sampling time= 640.5 ADC_12_IN4 clock cycles
	ADC_1->SQR1 &= ~(0b1111 << 0); // Set number of conversions to 1
	ADC_1->SQR1 |= 4 << 6; // 1st conversion is ADC_12_IN4
	ADC_1->CR |= (1 << 31); //calibrate ADC
	while ((ADC_1->CR & (1 << 31)) != 0) {} //wait until calibration is complete
	ADC_1->CR |= 1; //turn on ADC module
	while ((ADC_1->ISR & 1) == 0) {} //wait until ADC is ready
	ADC_1->IER |= (1 << 2); //turn on EOC interrupts
	ISER1 |= (1 << 5); //enable global signaling for ADC_1_2 interrupt
}

int get_button(uint32_t voltage) {

    if(voltage<2300){
        return -1;
    }
    else if(voltage<2600){
        return 0;
    }
    else if(voltage<2710){
        return 1;
    }
    else if(voltage<3000){
        return 2;
    }
    else if(voltage<3250){
        return 3;
    }
    else if(voltage<3600){
        return 4;
    }
    else if(voltage<3950){
        return 5;
    }
    else {
        return 6;
    }
    
}
