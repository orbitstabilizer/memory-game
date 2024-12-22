#ifndef __ADC_H
#define __ADC_H

#include <stdint.h>
#include "addresses.h"

typedef struct {
	volatile uint32_t ISR;
	volatile uint32_t IER;
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CFGR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	uint32_t RESERVED0;
	volatile uint32_t TR1;
	volatile uint32_t TR2;
	volatile uint32_t TR3;
	uint32_t RESERVED1;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t SQR4;
	volatile uint32_t DR;
	uint32_t RESERVED2;
	volatile uint32_t JSQR;
} ADC_TypeDef;

typedef struct {
	volatile uint32_t CSR; //0
	uint32_t reserved1; //4
	volatile uint32_t CCR; //8
	volatile uint32_t CDR; //C
} ADCCommon;

#define ADC_1	((ADC_TypeDef *)	0x42028000)
#define ADC ((ADCCommon *) 0x42028300)

void ADC1_2_IRQHandler();
void setup_adc();
int get_button(uint16_t voltage);

#endif
