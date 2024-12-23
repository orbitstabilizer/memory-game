#include "uart.h"

void send_message(MOVE move) {
    if (move.fail) {
        LPUART1->TDR = 'A' - 1;
    }
    else {
        LPUART1->TDR = 'A' + move.button * 5 + move.time;
    }
}

MOVE read_message() {
    uint8_t value = LPUART1->RDR;
    MOVE move;
    if (value == 'A' - 1) {
        move.fail = true;
    }
    else {
        move.button = (value - 'A') / 5;
        move.time = (value - 'A') % 5;
    }
    return move;
}


void LPUART1_initialization(void) {
    //Enable Clock for Power Interface.
    RCC_APB1ENR1 |= 1 << 28;
    // Change the regulator mode to Low-power mode.
    PWR_CR1|= 1<<14;
    // Turn VDDIO2 for PG[15:2] pins.
    PWR_CR2|= 1<<9;
    // Select SYSCLK (=4MHz) for the clock source of Low-power UART.
    RCC_CCIPR1 &= ~(1 << 11); RCC_CCIPR1 |= 1 << 10;
    // Enable GPIO G port for Tx and Rx pins.
    RCC_AHB2ENR|= 1<<6;
    // Set alternate function for PG7 and PG8.
    GPIOG->MODER &=~(0b0101 << (7 * 2));
    GPIOG->MODER |= 0b1010 << (7 * 2);
    // Connect PG7 to LPUART Tx.
    GPIOG->AFRL &= ~(0b0111 << (7 * 4));
    GPIOG->AFRL |= 0b1000 << (7 * 4);
    // Connect PG8 to LPUART Tx.
    GPIOG->AFRH &=~0b0111;
    GPIOG->AFRH |= 0b1000;
    // Enable Clock for LPUART.
    RCC_APB1ENR2 |= 1;
    // Set LPUART baud rate (BRR) for 115200 baud rate. 256 * 4000000 / 115200 for 115200 baud rate.
    LPUART1->BRR = 106666;
    // Enable FIFO.
    LPUART1->CR1 |= 1 << 29;
    // Enable Transmitter and Receiver.
    LPUART1->CR1 |= 0b11 << 2;
    // Enable interrupt for FIFO is not empty.
    LPUART1->CR1 |= 1 << 5;
    // Enable global signalling from ISER.
    ISER2 |= 1 << 2;
    // Enable LPUART.
    LPUART1->CR1 |= 1;
}
