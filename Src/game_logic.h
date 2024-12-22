#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"
#include "uart.h"
#include "move.h"
#include "time.h"
#include "interrupt.h"


typedef enum {
	OPPONENT,
	PLAYER,
	UNDEFINED,
} TURN;

extern TURN current_turn;


void reset_game();

void switch_turn();

void handle_player_turn(MOVE move);

void handle_opponents_turn(MOVE move);



#endif
