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
* Game structures and function declarations
*
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <cmath>

const int MAX_CMD_LEN = 256;

enum Player {
	P1 = 1,
	P2 = 2
};

enum Difficulty {
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
};

struct Move {
	int x;
	int y;
	int player;
};

struct GameState {
	int rows;
	int cols;
	int** board;
	Move* history;
	int historySize;
	int historyCap;
	int currentPlayer;
	bool vsRobot;
	Difficulty robotDiff;
};

void initGame(GameState& state, int n, int m, bool vsRobot = false, Difficulty diff = EASY);
void clearGame(GameState& state);
bool isValidMove(const GameState& state, int x, int y);

#endif
