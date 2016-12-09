#include "headers/Connect4.h"
#include <Windows.h>

#define USEARDUINO true	// comment out to compile without arduino support

#if USEARDUINO == true
#include "ofArduino.h"		// only need if using arduino
ofArduino ar;				// needed to be global so all the #if statements work correctly
#define numButtons 4
#define startPin 4
#endif // USEARDUINO

bool connected = false;  // is the arduino connected?

#define CPUMOVE rand()%7+1

//========================================================================
//	Takes an ofArduino object to read the pin states from
//	Return the int value of the button that was pressed
//	buttons need to be wired to pins sequntially increasing
//========================================================================
int checkButtons() {

//#if USEARUINO == true
	static int prev[4] = { -1 };	// buffer to hold previous states of pins
	static int curr[4] = { -1 };	// buffer to hold current states of pins

	for (int i = 0; i < numButtons; i++) {			// go through all the buttons and get their current states
		ar.update();								// update the values read from the arduino
		curr[i] = ar.getDigital(startPin + i);		// pins must be sequntial

		if (prev[i] == 1 && curr[i] != prev[i]) {	// check for button state change from pressed to released
			prev[i] = curr[i];
			return i + 1;			// return the button that was released
		}
		else {
			prev[i] = curr[i];		// update previous state
		}
	}

	return -1;		// return -1 if no button was pressed

//#else
//	return -1;
//#endif // USEARUINO == true

}

//========================================================================
//	Return the int value of the number key that was pressed
//========================================================================
int checkNumPress() {
	static int prev[10] = { -1 };	// buffer to hold previous state of keys
	static int curr[10] = { -1 };	// buffer to hold current state of keys

	for (int i = 0; i < 10; i++) {	// go through the keys 0-9 and get their current states
		curr[i] = ((GetKeyState(48 + i) >> 16) & 0x1);	// send ascii value of key; returns 16 bit number; leftmost bit signifies state of key.

		if (prev[i] == 1 && curr[i] != prev[i]) {	// check for key state change from pressed to released
			prev[i] = curr[i];
			return i;					// return the key that was released
		}
		else {
			prev[i] = curr[i];			// update previous state
		}
	}

	return -1;		// return -1 if no key was pressed
}

//========================================================================
//	Return the int value of the column selected
//========================================================================
int getColumn() {

	int numPress = checkNumPress();
	int buttonPushed = -1;
	if (connected)
		buttonPushed = checkButtons();

	if (numPress != -1)
		return numPress;
	else if (buttonPushed != -1)
		return buttonPushed;
	else
		return -1;
}

//--------------------Main Program----------------------------
int main(int argc, char* argv[]) {

#if USEARDUINO == true
	connected = ar.connect("COM4"); // connects to arduino; connected = true if succesfuly connected to arduino

	ar.sendDigitalPinMode(4, ARD_INPUT);
	ar.sendDigitalPinMode(5, ARD_INPUT);
	ar.sendDigitalPinMode(6, ARD_INPUT);
	ar.sendDigitalPinMode(7, ARD_INPUT);
#endif // USEARDUINO

	system(ERASE);
	//test
	Connect4 game1;		//initialize game
	string loadFile;    // name of the file to load save from
	int col = -1;		//initialize to allow into loop

	while (game1.menuOption == 3) {	//default constructor sets to 3
		game1.displayMenu();	//menuOption set to 1-3
		if (game1.menuOption == 3)
			game1.HowToPlay();
	}
	//-----------------------------------------------------------------------------------------------------------------------------------------------

	if (game1.menuOption == 1) {
		game1.newGame();
		game1.gameState = USER1_MOVE;
	}
	else {
		game1.gameState = LOAD;
	}

	game1.displayBoard();	//show board

	while (1) {

		switch (game1.gameState) {		// state machine of the main game loop
		case USER1_MOVE:
			game1.playerTurn = USER1;
			cout << "\nColumn 1-7? (Enter 0 to save) ";
			do {
				col = getColumn();
			} while (col == -1);

			if (col < 0 || col > 7)		// protect from invalid input
				continue;

			if (col == 0) {
				game1.gameState = SAVE;
				continue;
			}
			if (game1.board[col - 1].checkFull())	// column doesn't have room loop again
				continue;

			game1.makeMove(USER1, col);
			if (game1.gameFinished)				// game is done go to finished state
				game1.gameState = FINISHED;
			else if (game1.numPlayers == 1)		// should user2 or cpu have next move?
				game1.gameState = CPU_MOVE;
			else
				game1.gameState = USER2_MOVE;

			break;

		case USER2_MOVE:
			game1.playerTurn = USER2;
			cout << "\nColumn 1-7? (Enter 0 to save) ";
			do {
				col = getColumn();
			} while (col == -1);

			if (col < 0 || col > 7)		// protect from invalid input
				continue;

			if (col == 0) {
				game1.gameState = SAVE;
				continue;
			}
			if (game1.board[col - 1].checkFull())	// column doesn't have room loop again
				continue;

			game1.makeMove(USER2, col);		// make the move

			if (game1.gameFinished)
				game1.gameState = FINISHED;
			else
				game1.gameState = USER1_MOVE;

			break;

		case CPU_MOVE:
			col = CPUMOVE;
			if (game1.board[col - 1].checkFull())	//column doesn't have room loop again
				continue;

			game1.makeMove(CPU, col);		// make a move

			if (game1.gameFinished)
				game1.gameState = FINISHED;
			else
				game1.gameState = USER1_MOVE;
			break;

		case SAVE:
			game1.saveGame(game1.saveFile);
			cout << "\nThanks for playing\n";
			char c;
			cin >> c;
			return 1;

		case LOAD:
			loadFile = "save.txt";
			while (!game1.loadGame(loadFile)) {
				cout << "File " << loadFile << " could not be opened check filename and try again" << endl << "File to load: ";
				cin >> loadFile;
			}
			game1.displayBoard();
			break;

		case FINISHED:
			cout << game1.gameOverMessage;
			char ch;
			cin >> ch;
			return 1;
		}
	}
}
