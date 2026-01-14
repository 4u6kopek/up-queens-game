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

void resizeHistory(GameState& state) {
	int newCap = state.historyCap * 2;
	Move* newHist = new Move[newCap];
	for (int i = 0; i < state.historySize; ++i) {
		newHist[i] = state.history[i];
	}
	delete[] state.history;
	state.history = newHist;
	state.historyCap = newCap;
}

bool makeMove(GameState& state, int x, int y) {
	if (!isValidMove(state, x, y)) {
		return false;
	}

	state.board[x][y] = state.currentPlayer;

	if (state.historySize == state.historyCap) {
		resizeHistory(state);
	}

	state.history[state.historySize].x = x;
	state.history[state.historySize].y = y;
	state.history[state.historySize].player = state.currentPlayer;
	state.historySize++;

	state.currentPlayer = (state.currentPlayer == P1) ? P2 : P1;

	return true;
}

bool undoMove(GameState& state) {
	if (state.historySize == 0) {
		return false;
	}

	state.historySize--;
	Move last = state.history[state.historySize];
	state.board[last.x][last.y] = 0;

	state.currentPlayer = last.player;

	return true;
}

bool hasValidMoves(const GameState& state) {
	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			if (isValidMove(state, i, j)) {
				return true;
			}
		}
	}
	return false;
}

// UI
void printBoard(const GameState& state) {
	if (state.board == nullptr) return;

	std::cout << "  ";
	for (int j = 0; j < state.cols; ++j) {
		std::cout << j << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < state.rows; ++i) {
		std::cout << i << " ";
		for (int j = 0; j < state.cols; ++j) {
			if (state.board[i][j] == 0) {
				std::cout << ". ";
			}
			else {
				std::cout << "Q ";
			}
		}
		std::cout << "\n";
	}
}

void printFreeMoves(const GameState& state) {
	if (state.board == nullptr) return;

	std::cout << "Free: ";
	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			if (isValidMove(state, i, j)) {
				std::cout << "(" << i << "," << j << ") ";
			}
		}
	}
	std::cout << "\n";
}

void printHelp() {
	std::cout << "Commands:\n"
		<< "new N M [robot] [easy/medium/hard] - Start a new game\n"
		<< "play x y - Place a queen at coordinates\n"
		<< "free     - Show all valid moves\n"
		<< "show     - Display the board\n"
		<< "turn     - Whose turn is it\n"
		<< "back     - Undo last move\n"
		<< "save <file> - Save game state\n"
		<< "load <file> - Load game state\n"
		<< "exit     - Exit program\n";
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
