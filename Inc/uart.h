#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "addresses.h"
#include "move.h"
#include "game_logic.h"


void send_message(MOVE move);

MOVE read_message();

void LPUART1_initialization(void);

#endif