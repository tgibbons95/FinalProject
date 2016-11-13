#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#define EMPTY 0
#define USER1 1
#define USER2 2
#define CPU	  2

//--------------------Singular Game Piece---------------------
class gamePiece{
	private:
		int value;	//value in board
	public:
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

gamePiece::~gamePiece{
	//nothing to deallocate
}

//--------------------Singular Column (6 pieces)--------------
class boardColumn{
	private:
		bool full;	//True if the row is full
		vector<gamePiece> column;
	public:
		boardColumn();
		~boardColumn();
		void checkFull();	//change full if column has 6 members >0
};

boardColumn::boardColumn(){
	full=0;
}

boardColumn::~boardColumn(){
	//deallocate
}

void boardColumn::checkFull(){
	
}

//--------------------Main Program----------------------------
int main(int argc, char* argv[]){
	
	return 0;
}