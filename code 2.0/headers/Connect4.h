#pragma once
#include "gameBoard.h"

typedef enum state { USER1_MOVE = 1, USER2_MOVE, CPU_MOVE, SAVE, LOAD, FINISHED }States;

//--------------------Connect 4 Game---------------------
class Connect4 : public gameBoard {
public:
	//gameBoard mainBoard;


	//public:	
	Connect4();
	~Connect4();
	void displayMenu();
	void displayNumPlayers();
	void displayColor();
	void newGame();			//initialize new board
	int loadGame(string);	//load from file
	void saveGame(string);	//save to file
	void HowToPlay();		//load from file

	States gameState;
	int playerTurn = 1;
	int menuOption;
	string saveFile;
};