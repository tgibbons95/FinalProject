#pragma once

#include <string>
#include "headers/gameBoard.h"

typedef enum state { USER1_MOVE = 1, USER2_MOVE, CPU_MOVE, INIT, SAVE, LOAD, FINISHED }States;

#define CPUMOVE rand()%7+1
#define USEARDUINO false	// comment out to compile without arduino support

#if USEARDUINO == true
#include "ofArduino.h"		// only need if using arduino
ofArduino ar;				// needed to be global so all the #if statements work correctly
#define numButtons 4
#define startPin 4
#endif // USEARDUINO

//--------------------Connect 4 Game---------------------
class Connect4 {
private:
	gameBoard board;
	int numPlayers;		//1 or 2
	char playerColor;	//'R' or 'B'
	States gameState = INIT;
	int playerTurn = 1;
	string saveFile = "save.txt";
	string loadFile = "save.txt";
	bool connected = false;  // is the arduino connected?

	void newGame();			//initialize new board
	int loadGame(string);	//load from file
	void saveGame(string);	//save to file
	void HowToPlay();		//load from file
	int getColumnChoice();
	int checkNumPress();
	int checkButtons();

public:
	Connect4();
	~Connect4();

	void run();
	void init();
};