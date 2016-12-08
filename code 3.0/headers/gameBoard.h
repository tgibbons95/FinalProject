#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "boardColumn.h"

using namespace std;

//--------------------Singular Board (7 columns)--------------
class gameBoard {
private:
	char playerOneColor;	//'R' or 'B'
	bool gameFinished;
	vector<boardColumn> board;
	string gameOverMessage;

	bool chekcForWin(int, int);	//take indices of last move
	bool across(int, int);		//take indices true if 4 in a row across
	bool down(int, int);		//take indices true if 4 in a row down
	bool posDiagonal(int, int); //take indices true if 4 in a row diagonal(+)
	bool negDiagonal(int, int); //take indices true if 4 in a row diagonal(-)
	char symbol(int);

public:
	gameBoard();	//constructor
	~gameBoard();

	bool checkFull();			//change full if all columns full
	void displayBoard();		//print board
	void makeMove(int, int);	//take in player and move
	bool isGameOver();
	string getGOMsg();
	bool checkColumnFull(int col);
	int getPiece(int col, int row);
	void setPiece(int col, int row, int value);
	void incColHeight(int col);
	void zeroColHeight(int col);
	void setP1Color(char color);
};