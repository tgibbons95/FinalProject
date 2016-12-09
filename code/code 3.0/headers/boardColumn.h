#pragma once

#include <vector>
#include "gamePiece.h"

using namespace std;

#define EMPTY 0
#define USER1 1
#define USER2 2
#define CPU	  3

//--------------------Singular Column (6 pieces)--------------
class boardColumn {
	//friend class gameboard;

public:
	bool fullColumn;	//True if the row is full
	int length;			//how many pieces are in column
	vector<gamePiece> column;
	
	boardColumn();
	~boardColumn();

	bool checkColumnFull();	//change full if column has 6 members
};