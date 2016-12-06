#pragma once
#include "gameBoard.h"

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
	void loadGame(string);	//load from file
	void saveGame(string);	//save to file
	void HowToPlay();		//load from file

	int menuOption;
	string saveFile;
};