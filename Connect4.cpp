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

