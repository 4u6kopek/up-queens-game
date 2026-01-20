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
* Header file containing game structures and function declarations.
*
*/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <cmath>

const int MAX_CMD_LEN = 256;
const int MIN_DIM = 1;
const int MAX_DIM = 15;

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
	bool isStarted;
};

// Core Logic
void initGame(GameState& state, int n, int m, bool vsRobot = false, Difficulty diff = EASY);
void clearGame(GameState& state);
bool isValidMove(const GameState& state, int x, int y);
bool makeMove(GameState& state, int x, int y);
bool undoMove(GameState& state);
bool hasValidMoves(const GameState& state);

// AI Logic
void makeRobotMove(GameState& state);
int countFreeCells(const GameState& state);

// Persistence (Text-based)
bool saveGame(const GameState& state, const char* filename);
bool loadGame(GameState& state, const char* filename);

// UI Helpers
void printBoard(const GameState& state);
void printHistory(const GameState& state);
void printFreeMoves(const GameState& state);
void printHelp();

// Custom String Utilities
bool strEqual(const char* s1, const char* s2);
int strToInt(const char* s);
bool isNumber(const char* s);
int strLen(const char* s);

#endif
