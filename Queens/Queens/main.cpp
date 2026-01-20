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
* Entry point and command processing loop.
*
*/

#include "game.h"

const char* getNextToken(const char* cmd, char* token, int& pos) {
	while (cmd[pos] == ' ') {
		pos++;
	}
	if (cmd[pos] == '\0') {
		return nullptr;
	}
	int tPos = 0;
	while (cmd[pos] != ' ' && cmd[pos] != '\0') {
		token[tPos++] = cmd[pos++];
	}
	token[tPos] = '\0';
	return token;
}

void handleNew(GameState& state, const char* cmd) {
	char token[MAX_CMD_LEN];
	int pos = 0;
	getNextToken(cmd, token, pos); // skip 'new'
	if (!getNextToken(cmd, token, pos) || !isNumber(token)) return;
	int n = strToInt(token);
	if (!getNextToken(cmd, token, pos) || !isNumber(token)) return;
	int m = strToInt(token);
	if (n < MIN_DIM || n > MAX_DIM || m < MIN_DIM || m > MAX_DIM) {
		std::cout << "Dimensions must be between " << MIN_DIM << " and " << MAX_DIM << "!\n";
		return;
	}
	bool vsRobot = false;
	Difficulty diff = EASY;
	if (getNextToken(cmd, token, pos)) {
		if (strEqual(token, "robot")) {
			vsRobot = true;
			if (getNextToken(cmd, token, pos)) {
				if (strEqual(token, "medium")) diff = MEDIUM;
				else if (strEqual(token, "hard")) diff = HARD;
			}
		}
	}
	clearGame(state);
	initGame(state, n, m, vsRobot, diff);

	std::cout << "New game: " << n << "x" << m;
	if (vsRobot) {
		std::cout << " vs Robot (";
		switch (diff) {
		case EASY:   std::cout << "easy";   break;
		case MEDIUM: std::cout << "medium"; break;
		case HARD:   std::cout << "hard";   break;
		default:     std::cout << "unknown"; break;
		}
		std::cout << ")";
	}
	std::cout << "\n";
}

void handlePlay(GameState& state, const char* cmd) {
	char token[MAX_CMD_LEN];
	int pos = 0;
	getNextToken(cmd, token, pos); // skip 'play'
	if (!getNextToken(cmd, token, pos) || !isNumber(token)) {
		std::cout << "Invalid X coordinate!\n";
		return;
	}
	int x = strToInt(token);
	if (!getNextToken(cmd, token, pos) || !isNumber(token)) {
		std::cout << "Invalid Y coordinate!\n";
		return;
	}
	int y = strToInt(token);
	if (makeMove(state, x, y)) {
		if (state.vsRobot && hasValidMoves(state)) {
			makeRobotMove(state);
		}
	}
	else {
		std::cout << "Invalid move! Cell occupied or under attack.\n";
	}
}

void process(GameState& state, char* cmd, bool& running) {
	char token[MAX_CMD_LEN];
	int pos = 0;
	if (!getNextToken(cmd, token, pos)) return;
	if (strEqual(token, "new")) handleNew(state, cmd);
	else if (strEqual(token, "help")) printHelp();
	else if (strEqual(token, "exit")) running = false;
	else if (strEqual(token, "load")) {
		char file[MAX_CMD_LEN];
		if (getNextToken(cmd, file, pos)) {
			if (loadGame(state, file)) std::cout << "Loaded.\n";
			else std::cout << "Failed to load file.\n";
		}
	}
	else if (!state.isStarted) {
		std::cout << "No active game. Use 'new' or 'load' first.\n";
	}
	else {
		if (strEqual(token, "play")) handlePlay(state, cmd);
		else if (strEqual(token, "free")) printFreeMoves(state);
		else if (strEqual(token, "show")) printBoard(state);
		else if (strEqual(token, "turn")) std::cout << "Current: P" << state.currentPlayer << "\n";
		else if (strEqual(token, "back")) undoMove(state);
		else if (strEqual(token, "history")) printHistory(state);
		else if (strEqual(token, "save")) {
			char file[MAX_CMD_LEN];
			if (getNextToken(cmd, file, pos)) {
				if (saveGame(state, file)) std::cout << "Saved.\n";
			}
		}
		else std::cout << "Unknown command. Type 'help'.\n";
	}
	if (state.isStarted && !hasValidMoves(state)) {
		int winner = (state.currentPlayer == P1) ? P2 : P1;
		std::cout << "Game Over! Winner: P" << winner << "\n";
		printHistory(state);
		clearGame(state);
	}
}

int main() {
	GameState state = { 0, 0, nullptr, nullptr, 0, 0, P1, false, EASY, false };
	char cmd[MAX_CMD_LEN];
	bool running = true;
	std::cout << "Queens Game - FMI Edition\n";
	while (running) {
		std::cout << "> ";
		if (!std::cin.getline(cmd, MAX_CMD_LEN)) break;
		process(state, cmd, running);
	}
	clearGame(state);
	return 0;
}
