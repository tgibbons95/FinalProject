#include "headers/boardColumn.h"

boardColumn::boardColumn() {
	fullColumn = false;
	length = 0;
	int i;
	for (i = 0; i < 6; i++) {
		gamePiece current(EMPTY);	//create empty game pieces
		column.push_back(current);	//push 6 empty pieces to intialize
	}
}

boardColumn::~boardColumn() {
	//deallocate
}

bool boardColumn::checkFull() {
	if (length == 6)
		return true;
	else
		return false;
}