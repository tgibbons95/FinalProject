#pragma once

//--------------------Singular Game Piece---------------------
class gamePiece {
	//friend class boardColumn;
	//friend class gameboard;

public:
	int value;	//value in board
				//public:
	gamePiece();
	gamePiece(int);
	~gamePiece();
};