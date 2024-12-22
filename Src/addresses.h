#ifndef ADDRESSES_H
#define ADDRESSES_H

#include <stdint.h>

typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
	volatile uint32_t BRR;
	uint32_t reserved;
	volatile uint32_t SECCFGR;
} GPIOType;


typedef struct{
	volatile uint32_t CR1; //0
	volatile uint32_t CR2; //4
	volatile uint32_t CR3; //8
	volatile uint32_t BRR; //C
	uint32_t reserved1[2]; //10 14
	volatile uint32_t RQR; //18
	volatile uint32_t ISR; //1C
	volatile uint32_t ICR; //20
	volatile uint32_t RDR; //24
	volatile uint32_t TDR; //28
	volatile uint32_t PRESC; //2C
} LPUARTType;

typedef struct{
	volatile uint32_t CR1; //0
	volatile uint32_t CR2; //4
	volatile uint32_t CR3; //8
	volatile uint32_t BRR; //C
	volatile uint32_t GTPR; //10
	volatile uint32_t RTOR; //14
	volatile uint32_t RQR; //18
	volatile uint32_t ISR; //1C
	volatile uint32_t ICR; //20
	volatile uint32_t RDR; //24
	volatile uint32_t TDR; //28
	volatile uint32_t PRESC; //2C
} USARTType;


#define GPIOA ((GPIOType *) 0x42020000)
#define GPIOB ((GPIOType *) 0x42020400)
#define GPIOC ((GPIOType *) 0x42020800)
#define GPIOD ((GPIOType *) 0x42020C00)
#define GPIOE ((GPIOType *) 0x42021000)
#define GPIOF ((GPIOType *) 0x42021400)
#define GPIOG ((GPIOType *) 0x42021800)
#define GPIOH ((GPIOType *) 0x42021C00)

#define ISER3 *((volatile uint32_t *) 0xE000E10C)
#define ICER3 *((volatile uint32_t *) 0XE000E18C)
#define ISER2 *((volatile uint32_t *) 0xE000E108)
#define ICER2 *((volatile uint32_t *) 0XE000E188)
#define ISER1 *((volatile uint32_t*) 0xE000E104)
#define ICER1 *((volatile uint32_t *) 0XE000E184)

#define PWR_CR1 *((volatile uint32_t *) 0x40007000)
#define PWR_CR2 *((volatile uint32_t *) 0x40007004)

#define RCC_CFGR *((volatile uint32_t *) 0x40021008)
#define RCC_CR *((volatile uint32_t *) 0x40021000)
#define RCC_AHB2ENR *((volatile uint32_t *) 0x4002104C)
#define RCC_APB1ENR1 *((volatile uint32_t *) 0x40021058)
#define RCC_APB1ENR2 *((volatile uint32_t *) 0x4002105C)
#define RCC_APB2ENR *((volatile uint32_t *) 0x40021060)
#define RCC_CCIPR1 *((volatile uint32_t *) 0x40021088)


#define LPUART1 ((LPUARTType *) 0x40008000)
#define USART1 ((USARTType *) 0x40013800)
#define USART2 ((USARTType *) 0x40004400)
#define USART3 ((USARTType *) 0x40004800)
#define UART4 ((USARTType *) 0x40004C00)
#define UART5 ((USARTType *) 0x40005000)

#define __WFI __asm volatile ("wfi")

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


#endif
