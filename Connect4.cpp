#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define EMPTY 0
#define USER1 1
#define USER2 2
#define CPU	  2

//--------------------Singular Game Piece---------------------
class gamePiece{
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
	private:
		bool full;	//True if the row is full
	public:
		int length;	//how many pieces are in column
		vector<gamePiece> column;
		boardColumn();
		~boardColumn();
		void checkFull();	//change full if column has 6 members >0
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

void boardColumn::checkFull(){
	
}

//--------------------Singular Board (7 columns)--------------
class gameBoard{
	private:
		bool full;	//True if board is full
		vector<boardColumn> board;
	public:
		gameBoard();
		~gameBoard();
		void checkFull();	//change full if all columns full
		void displayBoard();	//print board
		char symbol(int);
		void makeMove(int,int);	//take in player and move
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

void gameBoard::checkFull(){
	
}

void gameBoard::displayBoard(){
	int r, c;
    
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
	int c=column-1;					//indices (r,c)
	int r=5-board[c].length;		//num of pieces in column
	
	board[c].column[r].value= player;	//change that one space
	//check for game over (not implemented)
	board[c].length++;	//one more piece added
}

//--------------------Connect 4 Game---------------------
class Connect4:public gameBoard{
	private:
		gameBoard board;
		char player1;	//'R' or 'B'
	public:	
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
	game1.displayBoard();
	game1.makeMove(USER1,4);
	game1.makeMove(USER2,3);
	game1.makeMove(USER1,3);
	game1.makeMove(USER2,3);
	game1.displayBoard();
	return 0;
}