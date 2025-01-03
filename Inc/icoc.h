/*
 * icoc.h
 *
 *  Created on: Dec 2, 2024
 *      Author: yusufakin
 */

#ifndef ICOC_H_
#define ICOC_H_


#include <stdint.h>
#include "gpio.h"
#include "time.h"
#include "move.h"


/*
 * utility macro, usage: __BFI( <lvalue>, <rvalue>, #lsb, #width)
 */
#define __BFI(rd, rs, lsb, width) do{\
	uint32_t __rs = rs;\
	__asm volatile(\
		"bfi %0, %1, #" #lsb ", #"#width\
		: "+r" (rd)\
		: "r"  (__rs)\
		: "cc"\
		);\
	}while(0);


#define __WFI __asm volatile ("wfi")


void setup_IC();
void setup_OC();
void TIM17_IRQHandler(void);

void play_tune(unsigned char note, uint16_t duration_ms, int is_melody);
void play_melody_from_moves(MOVE* moves, uint32_t len);
void play_saz_mix();
void setup_saz_mix();



#endif /* ICOC_H_ */
