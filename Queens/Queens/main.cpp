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
	getNextToken(cmd, token, pos);

	if (!getNextToken(cmd, token, pos)) return;
	int n = strToInt(token);

	if (!getNextToken(cmd, token, pos)) return;
	int m = strToInt(token);

	if (n < MIN_DIM || n > MAX_DIM || m < MIN_DIM || m > MAX_DIM) {
		std::cout << "Invalid dimensions!\n";
		return;
	}

	clearGame(state);
	initGame(state, n, m);
	std::cout << "Started " << n << "x" << m << " game.\n";
}

void handlePlay(GameState& state, const char* cmd) {
	if (state.board == nullptr) {
		std::cout << "No active game! Use 'new' first.\n";
		return;
	}

	char token[MAX_CMD_LEN];
	int pos = 0;
	getNextToken(cmd, token, pos);

	if (!getNextToken(cmd, token, pos)) return;
	int x = strToInt(token);

	if (!getNextToken(cmd, token, pos)) return;
	int y = strToInt(token);

	if (makeMove(state, x, y)) {
		std::cout << "Player " << (state.currentPlayer == P1 ? P2 : P1) << " moved to (" << x << "," << y << ").\n";
	}
	else {
		std::cout << "Invalid move! Cell is attacked or out of bounds.\n"; // ?Doesn't sound good?
	}
}

void process(GameState& state, char* cmd, bool& running) {
	char token[MAX_CMD_LEN];
	int pos = 0;
	if (!getNextToken(cmd, token, pos)) return;

	if (strEqual(token, "new")) {
		handleNew(state, cmd);
	}
	else if (strEqual(token, "play")) {
		handlePlay(state, cmd);
	}
	else if (strEqual(token, "free")) {
		printFreeMoves(state);
	}
	else if (strEqual(token, "turn")) {
		std::cout << "Current turn: P" << state.currentPlayer << "\n";
	}
	else if (strEqual(token, "back")) {
		if (undoMove(state)) std::cout << "Last move undone.\n";
		else std::cout << "No moves to undo.\n";
	}
	else if (strEqual(token, "history")) {
		printHistory(state);
	}
	else if (strEqual(token, "show")) {
		printBoard(state);
	}
	else if (strEqual(token, "help")) {
		printHelp();
	}
	else if (strEqual(token, "save") || strEqual(token, "load")) {
		char file[MAX_CMD_LEN];
		if (getNextToken(cmd, file, pos)) {
			if (token[0] == 's') {
				if (saveGame(state, file)) std::cout << "Game saved to " << file << "\n";
				else std::cout << "Failed to save game.\n";
			}
			else {
				if (loadGame(state, file)) std::cout << "Game loaded from " << file << "\n";
				else std::cout << "Failed to load game.\n";
			}
		}
		else {
			std::cout << "Usage: save/load <filename>\n";
		}
	}
	else if (strEqual(token, "exit")) {
		running = false;
	}
	else {
		std::cout << "Unknown command.\n";
	}

	if (state.board != nullptr && !hasValidMoves(state)) {
		int winner = (state.currentPlayer == P1) ? P2 : P1;
		std::cout << "Game Over! Winner: P" << winner << "\n";
		clearGame(state);
	}
}

int main() {
	GameState state = { 0, 0, nullptr, nullptr, 0, 0, P1, false, EASY };
	char cmd[MAX_CMD_LEN];
	bool running = true;

	std::cout << "Queens Game\n";
	std::cout << "Type 'new' to start or 'help' for commands.\n";

	while (running) {
		std::cout << "> ";
		if (!std::cin.getline(cmd, MAX_CMD_LEN)) {
			break;
		}
		process(state, cmd, running);
	}

	clearGame(state);
	return 0;
}
