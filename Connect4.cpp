#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <stdlib.h>
#define ERASE "CLS"	
//this is to erase screen after each turn but is system dependent
//see second line of display board

using namespace std;

#define EMPTY 0
#define USER1 1
#define USER2 2
#define CPU	  3
#define CPUMOVE rand()%7+1

//--------------------Singular Game Piece---------------------
class gamePiece{
	//friend class boardColumn;
	//friend class gameboard;
	
	public:
		int value;	//value in board
	//public:
		gamePiece();
		gamePiece(int);
		~gamePiece();
};

gamePiece::gamePiece(){
	value=0;
}

gamePiece::gamePiece(int player){
	value=player;
}

gamePiece::~gamePiece(){
	//nothing to deallocate
}

//--------------------Singular Column (6 pieces)--------------
class boardColumn{
	//friend class gameboard;
	
	public:
		bool fullColumn;	//True if the row is full
		int length;	//how many pieces are in column
		vector<gamePiece> column;
	//public:
		boardColumn();
		~boardColumn();
		bool checkFull();	//change full if column has 6 members >0
};

boardColumn::boardColumn(){
	fullColumn=false;
	length=0;
	int i;
	for(i=0; i<6; i++){
		gamePiece current(EMPTY);	//create empty game pieces
		column.push_back(current);	//push 6 empty pieces to intialize
	}
}

boardColumn::~boardColumn(){
	//deallocate
}

bool boardColumn::checkFull(){
	if(length==6)
		return true;
	else
		return false;
}

//--------------------Singular Board (7 columns)--------------
class gameBoard{
	public:
		bool fullBoard;	//True if board is full
		vector<boardColumn> board;
		bool gameFinished;
		int numPlayers;
		string gameOverMessage;
	//public:
		gameBoard();
		~gameBoard();
		bool checkFull();	//change full if all columns full
		void displayBoard();	//print board
		char symbol(int);
		void makeMove(int,int);	//take in player and move
		void gameOver(int,int);	//take indices of last move
		bool across(int, int); //take indices true if 4 in a row across
		bool down(int, int); //take indices true if 4 in a row down
		bool posDiagonal(int, int); //take indices true if 4 in a row diagonal(+)
		bool negDiagonal(int, int); //take indices true if 4 in a row diagonal(-)
};

gameBoard::gameBoard(){
	fullBoard=false;
	gameFinished=false;
	int i;
	for(i=0; i<7; i++){
		boardColumn current;	//create empty column
		board.push_back(current);	//push 7 empty columns to intialize
	}
	numPlayers=1;
}

gameBoard::~gameBoard(){
	//deallocate
}

bool gameBoard::checkFull(){
	for(int i=0; i<7; i++){
		if(!board[i].checkFull())	//if column found not full exit
			return false;
	}
	return true;	//if all column full, board is full return true
}

void gameBoard::displayBoard(){
	int r, c;
    system(ERASE);	//system dependent and can remove but looks nice
    cout << "  +---+---+---+---+---+---+---+\n";
    
    for (r=0; r<6; r++){
        cout << "  |";
        for (c=0; c<7; c++){
            cout << " " << symbol(board[c].column[5-r].value) << " |";
        }
        cout << "\n"
			 << "  +---+---+---+---+---+---+---+\n";
    }
    cout << "    1   2   3   4   5   6   7\n";	//print column nums
}

char gameBoard::symbol(int i) {

    switch(i)
    {
		case 0:
            return ' ';
        case 1:
            return 'R';  
        case 2:
			return 'B';  
		case 3:
			return 'B';  
    }
    return ('?');
}

void gameBoard::makeMove(int player, int column){
	if(column>=1 && column<=7){	//error check column choice
		int c=column-1;					//indices (r,c)
		int r=board[c].length;		//num of pieces in column
		
		if(board[c].checkFull()==false){	//error check for full column
			board[c].column[r].value= player;	//change that one space
			board[c].length++;	//one more piece added
			gameOver(r,c);	//check for game over
			if (numPlayers==1 && player==CPU) //display board for next player
				displayBoard();
			else if(gameFinished) //but display if game is over and cpu doesn't have to go
				displayBoard();
			//else no need to display for cpu
		}
		else
			cout << "\nColumn is full";
	}
	else	
		cout << "\nColumn must be 1-7";
}

void gameBoard::gameOver(int row, int col){
	//four across
	if(across(row,col))
		gameFinished=true;
	
	//four down(no need to check up)
	else if(down(row,col))
		gameFinished=true;
	
	//four diagonal	positive slope
	else if(posDiagonal(row,col))
		gameFinished=true;
	
	//four diagonal negative slope
	else if(negDiagonal(row,col))
		gameFinished=true;
	
	//Tie game
	else if(checkFull()){
		gameOverMessage="\nIt's a draw!\n";
		gameFinished=true;
	}
		
	//otherwise
	else
		gameFinished=false;
}

bool gameBoard::across(int row, int col){
	//which player to look for win
	int player=board[col].column[row].value;
	//what area to check for win
	int columnRangeLow=(col-3>=0)?col-3:0;
	int columnRangeHigh=(col+3<=6)?col+3:6;

	int count=0;	//how many in a row
	int x=0;		//bump indices
	
	while(col+x<=columnRangeHigh && board[col+x].column[row].value==player){
		count++;	//count piece and pieces to right
		x++;
	}
	x=1; //start one over to not double count move
	while(col-x>=columnRangeLow && board[col-x].column[row].value==player){
		count++;	//count pieces to left
		x++;
	}
	if(count>=4){
			if(player!=3){
				gameOverMessage="\nPlayer ";
				stringstream ss;	//sequence converts num to string 
				ss << player;
				gameOverMessage+= ss.str();
			}
			else
				gameOverMessage="CPU";	//for player=3 that is not actual player
			gameOverMessage+=" wins!\n";
			return true;
	}
	return false;
}

bool gameBoard::down(int row, int col){
	//which player to look for win
	int player=board[col].column[row].value;
	
	//what area to check for win
	int rowRangeLow=(row-3>=0)?row-3:0;
	int rowRangeHigh=(row+3<=5)?row+3:5;
	
	int count=0;	//how many in a column
	int x=0;		//bump indices
	
	while(row-x>=rowRangeLow && board[col].column[row-x].value==player){
		count++;	//count pieces down
		x++;
	}
	if(count>=4){
			if(player!=3){
				gameOverMessage="\nPlayer ";
				stringstream ss;	//sequence converts num to string 
				ss << player;
				gameOverMessage+= ss.str();
			}
			else
				gameOverMessage="CPU";	//for player=3 that is not actual player
			gameOverMessage+=" wins!\n";
			return true;
	}
	return false;
}

bool gameBoard::posDiagonal(int row, int col){
	//which player to look for win
	int player=board[col].column[row].value;
	//what area to check for win
	int columnRangeLow=(col-3>=0)?col-3:0;
	int columnRangeHigh=(col+3<=6)?col+3:6;
	int rowRangeLow=(row-3>=0)?row-3:0;
	int rowRangeHigh=(row+3<=5)?row+3:5;
	
	int count=0;	//how many in a row
	int x=0;		//bump indices
	
	while(row+x<=rowRangeHigh && col+x<=columnRangeHigh && board[col+x].column[row+x].value==player){
		count++;	//count piece and pieces to right
		x++;
	}
	x=1; //start one over to not double count move
	while(row-x>= rowRangeLow && col-x>=columnRangeLow && board[col-x].column[row-x].value==player){
		count++;	//count pieces to left
		x++;
	}
	//cout << count;
	if(count>=4){
			if(player!=3){
				gameOverMessage="\nPlayer ";
				stringstream ss;	//sequence converts num to string 
				ss << player;
				gameOverMessage+= ss.str();
			}
			else
				gameOverMessage="CPU";	//for player=3 that is not actual player
			gameOverMessage+=" wins!\n";
			return true;
	}
	return false;
}

bool gameBoard::negDiagonal(int row, int col){
	//which player to look for win
	int player=board[col].column[row].value;
	//what area to check for win
	int columnRangeLow=(col-3>=0)?col-3:0;
	int columnRangeHigh=(col+3<=6)?col+3:6;
	int rowRangeLow=(row-3>=0)?row-3:0;
	int rowRangeHigh=(row+3<=5)?row+3:5;
	
	int count=0;	//how many in a row
	int x=0;		//bump indices
	
	while(row+x<=rowRangeHigh && col-x>=columnRangeLow && board[col-x].column[row+x].value==player){
		count++;	//count piece and pieces to right
		x++;
	}
	x=1; //start one over to not double count move
	while(row-x>= rowRangeLow && col+x<=columnRangeHigh && board[col+x].column[row-x].value==player){
		count++;	//count pieces to left
		x++;
	}
	//cout << count;
	if(count>=4){
			if(player!=3){
				gameOverMessage="\nPlayer ";
				stringstream ss;	//sequence converts num to string 
				ss << player;
				gameOverMessage+= ss.str();
			}
			else
				gameOverMessage="CPU";	//for player=3 that is not actual player
			gameOverMessage+=" wins!\n";
			return true;
	}
	return false;
}

//--------------------Connect 4 Game---------------------
class Connect4:public gameBoard{
	public:
		//gameBoard mainBoard;
		char player1;	//'R' or 'B'
	//public:	
		Connect4();
		~Connect4();
		void displayMenu();	
		void newGame();			//initialize new board
		void loadGame(string);	//load from file
		void saveGame(string);	//save to file
		void HowToPlay();		//load from file
		
};

Connect4::Connect4():gameBoard(){
	player1='R';
}

Connect4::~Connect4(){
	//deallocate
}

//--------------------Main Program----------------------------
int main(int argc, char* argv[]){
	//test
	Connect4 game1;	//initialize game
	int col=0;		//initialize to allow into loop
	
	do{
		cout	<<	"\n1 or 2 Players?\t";
		cin 	>> game1.numPlayers;
	}
	while (game1.numPlayers!=1 && game1.numPlayers!=2);
	
	game1.displayBoard();	//show empty board
	bool preMoveFull=false;	//save whether column was full before move since it will be updated after
	while(true){
		while(col<1 || col>7 || preMoveFull){
			cout << "\nColumn? ";
			cin  >> col;
			preMoveFull=game1.board[col-1].checkFull();	//column doesn't have room loop again
			game1.makeMove(USER1,col);
		}
		col=0;
		
		if(game1.gameFinished){
			cout << game1.gameOverMessage;
			return 1;	//game finished
		}
		
		while(col<1 || col>7 || preMoveFull){
			if(game1.numPlayers==1){	//cpu makes move
				col=CPUMOVE;
				preMoveFull=game1.board[col-1].checkFull();	//column doesn't have room loop again
				game1.makeMove(CPU,col);
			}
			else{	//player 2 makes move
				cout << "\nColumn? ";
				cin  >> col;
				preMoveFull=game1.board[col-1].checkFull();	//column doesn't have room loop again
				game1.makeMove(USER2,col);
			}
		}
		col=0;

		if(game1.gameFinished){
			cout << game1.gameOverMessage;
			return 1;	//game finished
		}
	}
}

