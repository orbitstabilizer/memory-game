#include "game_logic.h"
#include "gpio.h"
#include "icoc.h"

TURN current_turn;
MOVE memory[100];
int current_memory_index = 0; // the number of buttons pressed for the player's current turn
int turn_counter = 0; // the number of turns

void reset_game() {
	current_turn = UNDEFINED;
	display.turn_indicator = 2;
	current_memory_index = 0;
	turn_counter = 0;
//	seven_segment_display(0);
	display.turn_counter = 1; //TODO:display
	display.button_indicator = 0;
	display.timer = 0;

//    TIM6->CR1 |= 1; // Enable timer.
}

bool is_current_move_correct(MOVE move) {
    if (memory[current_memory_index].button != move.button) {
        return false;
    }
    return memory[current_memory_index].time == move.time;
}


void switch_turn() {
	if (current_turn == PLAYER) {
		current_turn = OPPONENT; // Opponent's turn
		display.turn_indicator = 1;

	}
	else {
		current_turn = PLAYER; // Player's turn
		display.turn_indicator = 0;

	}
	display.turn_counter = (++turn_counter) + 1;
	current_memory_index = 0;
}

void handle_player_turn(MOVE move) {

    // If the first is from the player, then it is the player's turn
    if (current_turn == UNDEFINED) {
        current_turn = PLAYER;
		display.turn_indicator = 0;
//		turn_on_LED_BLUE(); // Turn on turn indicator LED  // TODO: display
    }

	if (current_memory_index == turn_counter) {
		// Player has correctly pressed all the buttons
		// Send the new move to the opponent
		send_message(move);
		// Add the message to the memory
		memory[turn_counter] = move;
		switch_turn();
	}
	else {
		if (is_current_move_correct(move)) {
			// Player has correctly pressed the button
			current_memory_index++;
			display.turn_counter--;
		}
		else {
			// Player has pressed the wrong button
			// Send the message to the opponent
			send_message((MOVE){0, 0, true});
//			turn_on_LED_RED(); // Lose indicator LED  // TODO: display
			reset_game();
		}
	}
}

void handle_opponents_turn(MOVE move) {
    // If the first is from the opponent, then it is the opponent's turn
    if (current_turn == UNDEFINED) {
        current_turn = OPPONENT;
		display.turn_indicator = 1;
//        TIM6->CR1 &= ~(1 << 0); // Disable timer.
    }

	// Opponent did not correctly press all the buttons
	if (move.fail) {
		// Current player wins
//		turn_on_LED_GREEN(); // Win indicator LED // TODO:display
		reset_game();
		return;
	}
	if (current_turn == PLAYER) {
		// Ignore the message
		return;
	}
	// Opponent pressed button 0 or 1 at the end, add 0 or 1 to memory
	memory[turn_counter] = move;
	display.button_indicator = move.button + 1;
	display.timer = move.time;

	// now, it is the player's turn
	switch_turn();
}
