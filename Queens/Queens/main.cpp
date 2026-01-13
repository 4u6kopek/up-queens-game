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

	initGame(state, 5, 5);
	std::cout << "5x5 board, curr player: P" << state.currentPlayer << "\n\n";

	if (makeMove(state, 0, 0)) {
		std::cout << "P1 placed queen at (0,0), nexct player: P" << state.currentPlayer << "\n";
	}

	if (makeMove(state, 1, 2)) {
		std::cout << "P2 placed queen at (1,2), next player: P" << state.currentPlayer << "\n";
	}

	printBoard(state);

	printFreeMoves(state);

	std::cout << "\nUndoing last move\n";
	if (undoMove(state)) {
		std::cout << "Undo successful. Curr player back to: P" << state.currentPlayer << "\n";
		printBoard(state);
	}

	clearGame(state);
	std::cout << "\nMemory cleared. Test passed.\n";

	return 0;
}
