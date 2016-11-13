#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

#define EMPTY 1
#define RED 2
#define REDKING 3
#define BLACK 4
#define BLACKKING 5

class player{
	
};

class board{
	private:
		int gameBoard[8][8];
	public:
		player Red;
		player Black;
		
		board();
		void displayBoard();
		char convertPiece(int);
};

board::board(){
	/*gameBoard=	{0,2,0,2,0,2,0,2},
					{2,0,2,0,2,0,2,0}, 
					{0,2,0,2,0,2,0,2}, 
					{1,0,1,0,1,0,1,0}, 
					{0,1,0,1,0,1,0,1}, 
					{4,0,4,0,4,0,4,0},
					{0,4,0,4,0,4,0,4},
					{4,0,4,0,4,0,4,0}};*/
	int i;
	for(i=0; i<8; i++){
		if(i%2 == 0){
			gameBoard[0][i]=0;
			gameBoard[1][i]=2;
			gameBoard[2][i]=0;
			gameBoard[3][i]=1;
			gameBoard[4][i]=0;
			gameBoard[5][i]=4;
			gameBoard[6][i]=0;
			gameBoard[7][i]=4;
		}
		else{
			gameBoard[0][i]=2;
			gameBoard[1][i]=0;
			gameBoard[2][i]=2;
			gameBoard[3][i]=0;
			gameBoard[4][i]=1;
			gameBoard[5][i]=0;
			gameBoard[6][i]=4;
			gameBoard[7][i]=0;
		}
	}
}

void board::displayBoard(){
	int r, c;
    
	printf("    a   b   c   d   e   f   g   h\n");
    printf("  +---+---+---+---+---+---+---+---+\n");
    
    for (r=0; r<8; r++)
    {
        printf("%d |", r+1);
        for (c=0; c<8; c++)
        {
            printf(" %c |", convertPiece(gameBoard[r][c]));
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
}

char board::convertPiece(int num){
	switch(num)
    {
		case 0:
            return ' ';
        case EMPTY:
            return '-';  
        case RED:
            return 'r';
        case REDKING:
            return 'R';  
		case BLACK:
            return 'b';
        case BLACKKING:
            return 'B'; 
    }
    return ('?');
	
}

int main(void){
	board checkers;
	checkers.displayBoard();
}