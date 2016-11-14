#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <stdlib.h>
#define ERASE "CLS"	
//this is to erase screen after each turn but is system dependent

using namespace std;

#define EMPTY 0
#define USER1 1
#define USER2 2
#define CPU	  2

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
		bool full;	//True if the row is full
		int length;	//how many pieces are in column
		vector<gamePiece> column;
	//public:
		boardColumn();
		~boardColumn();
		bool checkFull();	//change full if column has 6 members >0
};

boardColumn::boardColumn(){
	full=0;
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
		bool full;	//True if board is full
		vector<boardColumn> board;
	//public:
		gameBoard();
		~gameBoard();
		bool checkFull();	//change full if all columns full
		void displayBoard();	//print board
		char symbol(int);
		void makeMove(int,int);	//take in player and move
		void gameOver(int,int);	//take indices of last move
};

gameBoard::gameBoard(){
	full=0;
	int i;
	for(i=0; i<7; i++){
		boardColumn current;	//create empty column
		board.push_back(current);	//push 7 empty columns to intialize
	}
}

gameBoard::~gameBoard(){
	//deallocate
}

bool gameBoard::checkFull(){
	full=true;	//assume board full
	for(int i=0; i<7; i++){
		if(board[i].full!=1)	//if column found not full exit
			return false;
	}
}

void gameBoard::displayBoard(){
	int r, c;
    system(ERASE);
    cout << "  +---+---+---+---+---+---+---+\n";
    
    for (r=0; r<6; r++)
    {
        cout << "  |";
        for (c=0; c<7; c++)
        {
            cout << " " << symbol(board[c].column[r].value) << " |";
        }
        cout << "\n"
			 << "  +---+---+---+---+---+---+---+\n";
    }
    
    cout << "    1   2   3   4   5   6   7\n";
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
    }
    return ('?');
}

void gameBoard::makeMove(int player, int column){
	if(column>=1 && column<=7){	//error check column choice
		int c=column-1;					//indices (r,c)
		int r=5-board[c].length;		//num of pieces in column
		
		if(board[c].checkFull()==false){	//error check for full column
			board[c].column[r].value= player;	//change that one space
			board[c].length++;	//one more piece added
			//check for game over (not implemented)
			gameOver(r,c);
		}
		else
			cout << "\nColumn is full";
	}
	else	
		cout << "\nColumn must be 1-7";
}

void gameBoard::gameOver(int row, int col){
	//which player to look for win
	int player=board[col].column[row].value;
	//what area to check for win
	int rowRangeLow=(row>=1)?row:1;
	int rowRangeHigh=(row<=6)?row:6;
	int columnRangeLow=(col>=1)?col:1;
	int columnRangeHigh=(col<=7)?col:7;
	
	int count=0;	//how many in a row
	int x=0;		//bump indices
	//four across
	while(board[col].column[row+x].value==player){
		count++;
		x++;
	}
	x=0;
	while(board[col].column[row+x].value==player){
		count++;
		x--;
	}
	if(count>=4){
			cout << "\nPlayer " << player << " wins!" << endl;
			full=true;
	}
	//four down(no need to check up)
	//four diagonal	positive slope
	//four diagonal negative slope
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
	
}

Connect4::~Connect4(){
	//deallocate
}

//--------------------Main Program----------------------------
int main(int argc, char* argv[]){
	//test
	Connect4 game1;
	int col=0;
	game1.displayBoard();
	bool preMoveFull=false;
	while(true){
		while(col<1 || col>7 || preMoveFull){
			cout << "\nColumn? ";
			cin  >> col;
			preMoveFull=game1.board[col-1].checkFull();	//column doesn't have room loop again
			game1.makeMove(USER1,col);
		}
		col=0;
		game1.displayBoard();
		while(col<1 || col>7 || preMoveFull){
			cout << "\nColumn? ";
			cin  >> col;
			preMoveFull=game1.board[col-1].checkFull();	//column doesn't have room loop again
			game1.makeMove(USER2,col);
		}
		col=0;
		game1.displayBoard();
	}
	
	return 0;
}