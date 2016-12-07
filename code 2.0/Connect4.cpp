#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include <stdlib.h> //rand()

#include "headers/gamePiece.h"
#include "headers/gameBoard.h"
#include "headers/Connect4.h"

using namespace std;

Connect4::Connect4() : gameBoard() {
	menuOption = 3;
	saveFile = "save.txt";
}

Connect4::~Connect4() {
	//deallocate
}

void Connect4::displayNumPlayers(){
	do {
		cout << "\n1 or 2 Players?\t";
		cin >> numPlayers;
	} while (numPlayers != 1 && numPlayers != 2);
}

void Connect4::displayColor(){
	do {
		cout << "\nPlayer 1 Color? R or B?\t";
		cin >> playerColor;
		playerColor = toupper(playerColor);
	} while (playerColor != 'R' && playerColor != 'B');
}

void Connect4::displayMenu(){
	cout 	<< "\n\t1. New Game"
			<< "\n\t2. Load Game"
			<< "\n\t3. How to play\n" << endl;
			
	do{
		cout	<< "Choice:\t";
		cin		>> menuOption;
	} while (menuOption < 1 || menuOption > 3);
}

void Connect4::newGame(){
	//initialize new game
	system(ERASE);
	displayNumPlayers();
	displayColor();
}

int Connect4::loadGame(string loadFile){
	ifstream myfile;
	myfile.open(loadFile, ios::in);

	if (!myfile.is_open()) {
		return 0;
	}

	myfile >> playerTurn >> numPlayers >> playerColor;
	
	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 7; c++) {
			myfile >> board[c].column[5 - r].value;		// set gamePiece values
			if (board[c].column[5 - r].value != 0) {
				board[c].length++;						// keep track of how many are in each column
			}
		}
	}

	cout << loadFile << " has been read\n";
	myfile.close();
	return 1;
}

//--------------------------------------------------------------------------
//	save.txt format: [playerTurn] [numPlayers] [playerColor] [board layout]
//--------------------------------------------------------------------------
void Connect4::saveGame(string saveFile){
	ofstream myfile;
	myfile.open(saveFile, ios::out | ios::trunc);

	if(!myfile.is_open()){
		cout << saveFile << " could not be accessed\n";
	    return;
	}	
	
	myfile << playerTurn << " " << numPlayers << " " << playerColor << " ";

	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 7; c++) {
			myfile << board[c].column[5 - r].value << " ";
		}
	}
	
	cout << saveFile << " has been written\n";
	myfile.close();
	return;
}

void Connect4::HowToPlay(){
	string filename = "Instructions.txt";
	ifstream read;
	read.open(filename);
	
	if(!read.is_open()){
		cout << filename << " could not be accessed\n";
	    return;
	}
	
	cout << endl;

	string line;
	while (getline(read, line)) {
		cout << line << endl;
	}
	
	read.close();
	
	return;
}