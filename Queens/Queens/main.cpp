/**
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author <Bogomil Dimitrov>
* @idnumber <8MI0600665>
* @compiler VC
*
* Main entry point
*
*/

#include <iostream>
#include "game.h"

int main() {
	GameState state = { 0, 0, nullptr, nullptr, 0, 0, P1, false, EASY };

	std::cout << "Queens game initialized.\n";

	initGame(state, 8, 8);

	state.board[3][3] = P1;
	std::cout << "Placed a queen at 3, 3\n";

	printBoard(state);

	printFreeMoves(state);

	std::cout << "It works";

	clearGame(state);
	return 0;
}
