#ifndef __EXTI_H
#define __EXTI_H
#include <stdint.h>
#include "addresses.h"

typedef struct{
    volatile uint32_t RTSR1;
    volatile uint32_t FTSR1;
    volatile uint32_t SWIER1;
    volatile uint32_t RPR1;
    volatile uint32_t FPR1;
    volatile uint32_t SECCFGR1;
    volatile uint32_t PRIVCFG1;
    uint32_t reserved;
    volatile uint32_t RTSR2;
    volatile uint32_t FTSR2;
    volatile uint32_t SWIER2;
    volatile uint32_t RPR2;
    volatile uint32_t FPR2;
    volatile uint32_t SECCFG2;
    volatile uint32_t PRIVCFG2;
    uint32_t reserved1[9];
    volatile uint32_t EXTICR1;
    volatile uint32_t EXTICR2;
    volatile uint32_t EXTICR3;
    volatile uint32_t EXTICR4;
    volatile uint32_t LOCKR;
    uint32_t reserved2[3];
    volatile uint32_t IMR1;
    volatile uint32_t EMR1;
    uint32_t reserved3[2];
    volatile uint32_t IMR2;
    volatile uint32_t EMR2;
} EXTIBasicType;

#define EXTI ((EXTIBasicType *) 0x4002F400)

void EXTI5_IRQHandler();
void setup_exti();
void disable_exti();


#endif


