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

void process(GameState& state, char* cmd, bool& running) {
	char token[MAX_CMD_LEN];
	int pos = 0;
	if (!getNextToken(cmd, token, pos)) {
		return;
	}

	if (strEqual(token, "new")) {
		clearGame(state);
		initGame(state, 5, 5);
		std::cout << "Started new 5x5 game.\n";
	}
	else if (strEqual(token, "show")) {
		printBoard(state);
	}
	else if (strEqual(token, "help")) {
		printHelp();
	}
	else if (strEqual(token, "exit")) {
		running = false;
	}
	else {
		std::cout << "Unknown command. Type 'help' for info.\n";
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
