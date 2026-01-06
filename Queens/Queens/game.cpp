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
* Game logic implementation
*
*/
#include "game.h"

void initGame(GameState& state, int n, int m, bool vsRobot, Difficulty diff) {
	state.rows = n;
	state.cols = m;
	state.currentPlayer = P1;
	state.vsRobot = vsRobot;
	state.robotDiff = diff;
	state.historySize = 0;
	state.historyCap = 10;
	state.history = new Move[state.historyCap];

	state.board = new int* [n];
	for (int i = 0; i < n; ++i) {
		state.board[i] = new int[m];
		for (int j = 0; j < m; ++j) {
			state.board[i][j] = 0;
		}
	}
}

void clearGame(GameState& state) {
	if (state.board != nullptr) {
		for (int i = 0; i < state.rows; ++i) {
			delete[] state.board[i];
		}
		delete[] state.board;
		state.board = nullptr;
	}
	delete[] state.history;
	state.history = nullptr;
	state.historySize = 0;
}
