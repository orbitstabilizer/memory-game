/*
 * time.h
 *
 *  Created on: Dec 21, 2024
 *      Author: USER
 */

#ifndef TIME_H_
#define TIME_H_

typedef struct{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    uint32_t reserved;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    uint32_t reserved1[3];
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIMxBasicType;


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	uint32_t _0;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	uint32_t _1;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	uint32_t _2[3];
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR1;
	uint32_t _3[3];
	volatile uint32_t OR2;
} TIM16_17_t;

#define TIM6 ((TIMxBasicType *) 0x40001000)
#define TIM16 ((TIM16_17_t *) 0x40014400)
#define TIM17 ((TIM16_17_t *) 0x40014800)


#endif /* TIME_H_ */
