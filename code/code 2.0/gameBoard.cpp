#include "headers/gameBoard.h"

gameBoard::gameBoard() {
	fullBoard = false;
	gameFinished = false;
	int i;
	for (i = 0; i < 7; i++) {
		boardColumn current;		//create empty column
		board.push_back(current);	//push 7 empty columns to intialize
	}

	numPlayers = 1;
	playerColor = 'R';
}

gameBoard::~gameBoard() {
	//deallocate
}

bool gameBoard::checkFull() {
	for (int i = 0; i < 7; i++) {
		if (!board[i].checkFull())	//if column found not full exit
			return false;
	}
	return true;	//if all column full, board is full return true
}

void gameBoard::displayBoard() {
	int r, c;
	system(ERASE);	//system dependent and can remove but looks nice
	cout << "  +---+---+---+---+---+---+---+\n";

	for (r = 0; r < 6; r++) {
		cout << "  |";
		for (c = 0; c < 7; c++) {
			cout << " " << symbol(board[c].column[5 - r].value) << " |";
		}
		cout << "\n"
			<< "  +---+---+---+---+---+---+---+\n";
	}
	cout << "    1   2   3   4   5   6   7\n";	//print column nums
	
	//cout << "\n It is Player"
}

char gameBoard::symbol(int i) {

	switch (i) {
	case 0:
		return ' ';
	case 1:
		return playerColor;
	case 2:
		if (playerColor == 'R')
			return 'B';
		else
			return 'R';
	case 3:
		if (playerColor == 'R')
			return 'B';
		else
			return 'R';
	}
	return ('?');
}

void gameBoard::makeMove(int player, int column) {
	if (column >= 1 && column <= 7) {		//error check column choice
		int c = column - 1;					//indices (r,c)
		int r = board[c].length;			//num of pieces in column

		if (board[c].checkFull() == false) {	//error check for full column
			board[c].column[r].value = player;	//change that one space
			board[c].length++;					//one more piece added
			gameOver(r, c);						//check for game over
			if (numPlayers == 2)				//display board for next player
				displayBoard();
			else if (player == CPU)
				displayBoard();
			else if (gameFinished)			//but display if game is over and cpu doesn't have to go
				displayBoard();
											//else no need to display for cpu
		}
		else
			cout << "\nColumn is full";
	}
	else
		cout << "\nColumn must be 1-7";
}

void gameBoard::gameOver(int row, int col) {
	//four across
	if (across(row, col))
		gameFinished = true;

	//four down(no need to check up)
	else if (down(row, col))
		gameFinished = true;

	//four diagonal	positive slope
	else if (posDiagonal(row, col))
		gameFinished = true;

	//four diagonal negative slope
	else if (negDiagonal(row, col))
		gameFinished = true;

	//Tie game
	else if (checkFull()) {
		gameOverMessage = "\nIt's a draw!\n";
		gameFinished = true;
	}

	//otherwise
	else
		gameFinished = false;
}

bool gameBoard::across(int row, int col) {
	//which player to look for win
	int player = board[col].column[row].value;
	//what area to check for win
	int columnRangeLow = (col - 3 >= 0) ? col - 3 : 0;
	int columnRangeHigh = (col + 3 <= 6) ? col + 3 : 6;

	int count = 0;	//how many in a row
	int x = 0;		//bump indicesi

	while (col + x <= columnRangeHigh && board[col + x].column[row].value == player) {
		count++;	//count piece and pieces to right
		x++;
	}
	x = 1; //start one over to not double count move
	while (col - x >= columnRangeLow && board[col - x].column[row].value == player) {
		count++;	//count pieces to left
		x++;
	}
	if (count >= 4) {
		if (player != 3) {
			gameOverMessage = "\nPlayer ";
			stringstream ss;	//sequence converts num to string 
			ss << player;
			gameOverMessage += ss.str();
		}
		else
			gameOverMessage = "CPU";	//for player=3 that is not actual player
		gameOverMessage += " wins!\n";
		return true;
	}
	return false;
}

bool gameBoard::down(int row, int col) {
	//which player to look for win
	int player = board[col].column[row].value;

	//what area to check for win
	int rowRangeLow = (row - 3 >= 0) ? row - 3 : 0;
	int rowRangeHigh = (row + 3 <= 5) ? row + 3 : 5;

	int count = 0;	//how many in a column
	int x = 0;		//bump indices

	while (row - x >= rowRangeLow && board[col].column[row - x].value == player) {
		count++;	//count pieces down
		x++;
	}
	if (count >= 4) {
		if (player != 3) {
			gameOverMessage = "\nPlayer ";
			stringstream ss;	//sequence converts num to string 
			ss << player;
			gameOverMessage += ss.str();
		}
		else
			gameOverMessage = "CPU";	//for player=3 that is not actual player
		gameOverMessage += " wins!\n";
		return true;
	}
	return false;
}

bool gameBoard::posDiagonal(int row, int col) {
	//which player to look for win
	int player = board[col].column[row].value;
	//what area to check for win
	int columnRangeLow = (col - 3 >= 0) ? col - 3 : 0;
	int columnRangeHigh = (col + 3 <= 6) ? col + 3 : 6;
	int rowRangeLow = (row - 3 >= 0) ? row - 3 : 0;
	int rowRangeHigh = (row + 3 <= 5) ? row + 3 : 5;

	int count = 0;	//how many in a row
	int x = 0;		//bump indices

	while (row + x <= rowRangeHigh && col + x <= columnRangeHigh && board[col + x].column[row + x].value == player) {
		count++;	//count piece and pieces to right
		x++;
	}
	x = 1; //start one over to not double count move
	while (row - x >= rowRangeLow && col - x >= columnRangeLow && board[col - x].column[row - x].value == player) {
		count++;	//count pieces to left
		x++;
	}
	//cout << count;
	if (count >= 4) {
		if (player != 3) {
			gameOverMessage = "\nPlayer ";
			stringstream ss;	//sequence converts num to string 
			ss << player;
			gameOverMessage += ss.str();
		}
		else
			gameOverMessage = "CPU";	//for player=3 that is not actual player
		gameOverMessage += " wins!\n";
		return true;
	}
	return false;
}

bool gameBoard::negDiagonal(int row, int col) {
	//which player to look for win
	int player = board[col].column[row].value;
	//what area to check for win
	int columnRangeLow = (col - 3 >= 0) ? col - 3 : 0;
	int columnRangeHigh = (col + 3 <= 6) ? col + 3 : 6;
	int rowRangeLow = (row - 3 >= 0) ? row - 3 : 0;
	int rowRangeHigh = (row + 3 <= 5) ? row + 3 : 5;

	int count = 0;	//how many in a row
	int x = 0;		//bump indices

	while (row + x <= rowRangeHigh && col - x >= columnRangeLow && board[col - x].column[row + x].value == player) {
		count++;	//count piece and pieces to right
		x++;
	}
	x = 1; //start one over to not double count move
	while (row - x >= rowRangeLow && col + x <= columnRangeHigh && board[col + x].column[row - x].value == player) {
		count++;	//count pieces to left
		x++;
	}
	//cout << count;
	if (count >= 4) {
		if (player != 3) {
			gameOverMessage = "\nPlayer ";
			stringstream ss;	//sequence converts num to string 
			ss << player;
			gameOverMessage += ss.str();
		}
		else
			gameOverMessage = "CPU";	//for player=3 that is not actual player
		gameOverMessage += " wins!\n";
		return true;
	}
	return false;
}