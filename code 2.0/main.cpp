#include "headers\Connect4.h"

#define CPUMOVE rand()%7+1

//--------------------Main Program----------------------------
int main(int argc, char* argv[]) {
	system(ERASE);
	//test
	Connect4 game1;	//initialize game
	int col = -1;		//initialize to allow into loop

	while (game1.menuOption == 3) {	//default constructor sets to 3
		game1.displayMenu();	//menuOption set to 1-3
		if (game1.menuOption == 3)
			game1.HowToPlay();
	}

	if (game1.menuOption == 1)	//new game
		game1.newGame();
	else {	//load game
		string loadFile;
		cout << "\nFile to load: ";
		cin >> loadFile;
		game1.loadGame(loadFile);
	}

	game1.displayBoard();	//show board

	bool preMoveFull = false;	//save whether column was full before move since it will be updated after
	while (true) {
		while (col<0 || col>7 || preMoveFull) {
			cout << "\nColumn 1-7? (Enter 0 to save) ";
			cin >> col;
			if (col == 0) {
				game1.saveGame(game1.saveFile);
				cout << "\nThanks for playing\n";
				return 1;
			}
			preMoveFull = game1.board[col - 1].checkFull();	//column doesn't have room loop again
			game1.makeMove(USER1, col);
		}
		col = -1;

		if (game1.gameFinished) {
			cout << game1.gameOverMessage;
			return 1;	//game finished
		}

		while (col<0 || col>7 || preMoveFull) {
			if (game1.numPlayers == 1) {	//cpu makes move
				col = CPUMOVE;
				preMoveFull = game1.board[col - 1].checkFull();	//column doesn't have room loop again
				game1.makeMove(CPU, col);
			}
			else {	//player 2 makes move
				cout << "\nColumn? (Enter 0 to save) ";
				cin >> col;
				if (col == 0) {
					game1.saveGame(game1.saveFile);
					cout << "\nThanks for playing\n";
					return 1;
				}
				preMoveFull = game1.board[col - 1].checkFull();	//column doesn't have room loop again
				game1.makeMove(USER2, col);
			}
		}
		col = -1;

		if (game1.gameFinished) {
			cout << game1.gameOverMessage;
			return 1;	//game finished
		}
	}
}