/**
*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Bogomil Dimitrov
* @idnumber 8MI0600665
* @compiler VC
*
* Implementation of game logic, AI and persistence.
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
	state.isStarted = true;
}

void clearGame(GameState& state) {
	if (state.board != nullptr) {
		for (int i = 0; i < state.rows; ++i) {
			delete[] state.board[i];
		}
		delete[] state.board;
		state.board = nullptr;
	}
	if (state.history != nullptr) {
		delete[] state.history;
		state.history = nullptr;
	}
	state.historySize = 0;
	state.isStarted = false;
}

bool isValidMove(const GameState& state, int x, int y) {
	if (x < 0 || x >= state.rows || y < 0 || y >= state.cols) {
		return false;
	}
	if (state.board[x][y] != 0) {
		return false;
	}
	// Check row, column, and diagonals for existing queens
	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			if (state.board[i][j] != 0) {
				if (i == x || j == y || abs(i - x) == abs(j - y)) {
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

int countFreeCells(const GameState& state) {
	int count = 0;
	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			if (isValidMove(state, i, j)) {
				count++;
			}
		}
	}
	return count;
}

void makeRobotMove(GameState& state) {
	int bestX = -1, bestY = -1;

	if (state.robotDiff == EASY) {
		// Easy: First available move 
		for (int i = 0; i < state.rows; ++i) {
			for (int j = 0; j < state.cols; ++j) {
				if (isValidMove(state, i, j)) {
					makeMove(state, i, j);
					return;
				}
			}
		}
	}
	else if (state.robotDiff == MEDIUM) {
		// Medium: Edge-priority 
		int minEdgeDist = 1000;
		for (int i = 0; i < state.rows; ++i) {
			for (int j = 0; j < state.cols; ++j) {
				if (isValidMove(state, i, j)) {
					int d1 = (i < state.rows - 1 - i) ? i : (state.rows - 1 - i);
					int d2 = (j < state.cols - 1 - j) ? j : (state.cols - 1 - j);
					int currentDist = (d1 < d2) ? d1 : d2;
					if (currentDist < minEdgeDist) {
						minEdgeDist = currentDist;
						bestX = i;
						bestY = j;
					}
				}
			}
		}
	}
	else {
		// Hard: Minimizing opponent's valid moves
		int minOpponentMoves = 10000;

		for (int i = 0; i < state.rows; ++i) {
			for (int j = 0; j < state.cols; ++j) {
				if (isValidMove(state, i, j)) {
					state.board[i][j] = state.currentPlayer;
					int freeAfterMove = countFreeCells(state);
					state.board[i][j] = 0;

					if (freeAfterMove < minOpponentMoves) {
						minOpponentMoves = freeAfterMove;
						bestX = i;
						bestY = j;
					}
				}
			}
		}
	}

	if (bestX != -1) {
		makeMove(state, bestX, bestY);
	}
}

bool saveGame(const GameState& state, const char* filename) {
	std::ofstream ofs(filename);
	if (!ofs.is_open()) {
		return false;
	}
	ofs << state.rows << " " << state.cols << " " << state.currentPlayer << " "
		<< state.vsRobot << " " << (int)state.robotDiff << "\n";
	for (int i = 0; i < state.rows; ++i) {
		for (int j = 0; j < state.cols; ++j) {
			ofs << state.board[i][j] << (j == state.cols - 1 ? "" : " ");
		}
		ofs << "\n";
	}
	ofs << state.historySize << "\n";
	for (int i = 0; i < state.historySize; ++i) {
		ofs << state.history[i].x << " " << state.history[i].y << " " << state.history[i].player << "\n";
	}
	ofs.close();
	return true;
}

bool loadGame(GameState& state, const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		return false;
	}
	clearGame(state);
	int diffInt;
	if (!(ifs >> state.rows >> state.cols >> state.currentPlayer >> state.vsRobot >> diffInt)) {
		return false;
	}
	state.robotDiff = (Difficulty)diffInt;
	state.board = new int* [state.rows];
	for (int i = 0; i < state.rows; ++i) {
		state.board[i] = new int[state.cols];
		for (int j = 0; j < state.cols; ++j) {
			ifs >> state.board[i][j];
		}
	}
	ifs >> state.historySize;
	state.historyCap = state.historySize + 10;
	state.history = new Move[state.historyCap];
	for (int i = 0; i < state.historySize; ++i) {
		ifs >> state.history[i].x >> state.history[i].y >> state.history[i].player;
	}
	ifs.close();
	state.isStarted = true;
	return true;
}

void printBoard(const GameState& state) {
	std::cout << "  ";
	for (int j = 0; j < state.cols; ++j) {
		std::cout << j << (j < 10 ? " " : "");
	}
	std::cout << "\n";
	for (int i = 0; i < state.rows; ++i) {
		std::cout << i << (i < 10 ? " " : "");
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

void printHistory(const GameState& state) {
	if (state.historySize == 0) {
		std::cout << "No moves yet.\n";
		return;
	}
	for (int i = 0; i < state.historySize; ++i) {
		std::cout << "Move " << i + 1 << ": P" << state.history[i].player
			<< " -> (" << state.history[i].x << "," << state.history[i].y << ")\n";
	}
}

void printFreeMoves(const GameState& state) {
	std::cout << "Free cells: ";
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
		<< "new N M [robot] [easy/medium/hard] - Start new game (max 15x15)\n"
		<< "play x y - Place a queen\n"
		<< "free - Show valid moves\n"
		<< "show - Display board\n"
		<< "save <file> - Save to text file\n"
		<< "load <file> - Load from text file\n"
		<< "turn - Show current player\n"
		<< "back - Undo last move\n"
		<< "history - Show move history\n"
		<< "help - Show this list\n"
		<< "exit - Quit\n";
}

bool strEqual(const char* s1, const char* s2) {
	if (!s1 || !s2) {
		return false;
	}
	while (*s1 && *s2) {
		if (*s1 != *s2) {
			return false;
		}
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

bool isNumber(const char* s) {
	if (!s || *s == '\0') {
		return false;
	}
	while (*s) {
		if (*s < '0' || *s > '9') {
			return false;
		}
		s++;
	}
	return true;
}

int strLen(const char* s) {
	int len = 0;
	while (s[len]) {
		len++;
	}
	return len;
}
