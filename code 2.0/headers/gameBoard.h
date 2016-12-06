#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "boardColumn.h"

using namespace std;

// define macro for clearing the screen
#ifdef _WIN32		// compile only on windows systems
#define ERASE "cls"	
#endif

#ifdef linux		// compile only on linux systems
#define ERASE "clear"
#endif

//--------------------Singular Board (7 columns)--------------
class gameBoard {
public:
	bool fullBoard;		//True if board is full
	vector<boardColumn> board;
	bool gameFinished;
	int numPlayers;		//1 or 2
	char playerColor;	//'R' or 'B'
	string gameOverMessage;

//public:
	gameBoard();	//constructor
	~gameBoard();

	bool checkFull();			//change full if all columns full
	void displayBoard();		//print board
	char symbol(int);
	void makeMove(int, int);	//take in player and move

	void gameOver(int, int);	//take indices of last move
	bool across(int, int);		//take indices true if 4 in a row across
	bool down(int, int);		//take indices true if 4 in a row down
	bool posDiagonal(int, int); //take indices true if 4 in a row diagonal(+)
	bool negDiagonal(int, int); //take indices true if 4 in a row diagonal(-)
};