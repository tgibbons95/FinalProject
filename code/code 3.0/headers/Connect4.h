#pragma once

#include <string>
#include "headers/gameBoard.h"

typedef enum state { USER1_MOVE = 1, USER2_MOVE, CPU_MOVE, MENU, SAVE, LOAD, FINISHED }States;

#define USEARDUINO false	// set to false to compile without arduino support

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
	int numPlayers = 1;				// 1 or 2
	int playerTurn = 1;				// keep track of whos turn it is
	char playerColor = 'R';			//'R' or 'B'
	States gameState = MENU;		// The state of the main game loop; start at the MENU state
	string saveFile = "save.txt";	// file to save and load the game state
	string loadFile = "save.txt";
	bool connected = false;			// is the arduino connected?

	void newGame();			// initialize new board
	int loadGame(string);	// load from file
	void saveGame(string);	// save to file
	void HowToPlay();		// load from file
	int getColumnChoice();	// get the column the user wants to make a move in; calls checkNumPress() and checkButtons();
	int checkNumPress();	// polls the keyboard for current key states
	int checkButtons();		// polls the arduion for current button states

public:
	Connect4();
	~Connect4();

	void run();				// run the main game loop
	void init();			// initialize the game
};