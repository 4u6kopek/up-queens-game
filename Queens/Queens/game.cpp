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

bool isValidMove(const GameState& state, int x, int y) {
	if (x < 0 || x >= state.rows || y < 0 || y >= state.cols) {
		return false;
	}

	if (state.board[x][y] != 0) {
		return false;
	}

	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			if (state.board[i][j] != 0) {

				if (i == x || j == y) {
					return false;
				}

				if (abs(i - x) == abs(j - y)) {
					return false;
				}
			}
		}
	}
	return true;
}




// string u func
bool strEqual(const char* s1, const char* s2) {
	if (!s1 || !s2) return false;
	while (*s1 && *s2) {
		if (*s1 != *s2) return false;
		s1++;
		s2++;
	}
	return *s1 == *s2;
}

int strToInt(const char* s) {
	int res = 0;
	while (*s >= '0' && *s <= '9') {
		res = res * 10 + (*s - '0');
		s++;
	}
	return res;
}

void strCopy(char* dest, const char* src) {
	while (*src) {
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}

int strLen(const char* s) {
	int len = 0;
	while (s[len]) len++;
	return len;
}

bool isDigit(char c) {
	return c >= '0' && c <= '9';
}
