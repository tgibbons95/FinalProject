/*
  
*/


#include<stdio.h>

#define ROWS 8
#define COLS 8

#define EMPTY 1
#define RED 2
#define BLACK 3
#define REDKING 4
#define BLACKKING 5


#define ISRED(c)  (c == RED || c == REDKING)
#define ISBLACK(c) (c == BLACK || c == BLACKKING))
#define ISEMPTY(c) (c == 1)


void printDisplay(int d[][COLS]);
void swapIJKL(int d[ROWS][COLS], int i, int j, int k, int l);
char value2symbol(int i);
void printDisplayFancy(int d[][COLS]);
int Playersturn(int d[][COLS], int player,int i,int j,int k,int l);

void printDisplayFancy(int d[][COLS])
{
    int rr, cc, pp;
    
    printf("  +---+---+---+---+---+---+---+---+\n");
    
    for (rr=0; rr<ROWS; ++rr)
    {
        printf("%d |", rr+1);
        for (cc=0; cc<COLS; ++cc)
        {
            printf(" %c |", value2symbol(d[rr][cc]) );
        }
        printf("\n");
        printf("  +---+---+---+---+---+---+---+---+\n");
    }
    
    printf("    a   b   c   d   e   f   g   h\n");
}

void swapIJKL(int d[ROWS][COLS], int i, int j, int k, int l)
{
    int temp;
    
    printf("SWAP: %d,%d to %d,%d\n", i, j, k, l);
    
    temp = d[i][j];
    
    d[i][j] = d[k][l];
    
    d[k][l] = temp;


}



char value2symbol(int i) 
{

    switch(i)
    {
  	case 0:
            return ' ';
        case 1:
            return 'E';  
        case 2:
            return '$';
        case 3:
            return '@';     
    }
    return ('?');
}

int Playersturn(int d[][COLS], int player,int i,int j,int k,int l)
{
    int jmp_r;
    int jmp_c;
    
    if(player == RED){
        printf("RED move from %d,%d to %d,%d\n", i, j, k, l);
    } else {
        printf("BLACK move from %d,%d to %d,%d\n", i, j, k, l);
    }
    
    if(i < 0 && ROWS <= i){ // keeping in bounds
        printf("i is out of bounds\n");
        return -1;
    }
    if(j < 0 && COLS <= j){
        printf("j is out of bound");
        return -1;
    }
        
    if(k < 0 && ROWS <= k){
        printf("k is out of bounds");
        return -1;
        
    }
    if(l < 0 && COLS<= l){
        printf("l is out of bounds\n");
        return -1;
    }
        
    // check player is moving his own piece.
    if(player == RED){
        if(d[i][j] != RED){
            printf("move your own piece!\n");
            return -1;
        }
    } else { //BLACK
        if(d[i][j] != BLACK){
            printf("move your own piece!\n");
            return -1;
        }
    }
    
    //make sure they are umping to a empty loacation
    if(d[k][l] != EMPTY){
        printf("You must move to a empty location");
        return -1;
    }
    
    
    
    
    
    // make sure the vertical direction of the move is not illegal
    if(player == RED){
        //make sure he moves down
        if(i >= k){
            printf("RED player must move down\n");
            return -1;
        }
    } else { //BLACK
        // make sure player moves up
        if(i <= k){
            printf("BLACK player must move up\n");   
            return -1;
        }
    }
    
    
    // check if it's a regular move
    if(i - k == -1 || i - k == 1){
        if(j - l == 1 || j - l == -1){
            swapIJKL(d,i,j,k,l);
            return 0;
        }
    }
    
    //check if it's a jump move
    if(i - k == -2 || i - k == 2){
        if(j - l == -2 || j - l == 2){
            // check if the jump position is enemy
            if(i < k){ // move down
                jmp_r = i + 1;
            } else { // move up
                jmp_r = i - 1;
            }
            if(j < l){ // move down
                jmp_c = j + 1;
            } else { // move up
                jmp_c = j - 1;
            }
            
            if(player==RED && d[jmp_r][jmp_c]!=BLACK)
            {
                printf("Enemeny is not Canadian at %d%d",jmp_r, jmp_c);
                return -1;
            }
            if(player==BLACK && d[jmp_r][jmp_c] != RED){
                printf("you can only jump over an enemy player\n");
                return -1;
            }
            
            // we are sure the move is valid:
            d[jmp_r][jmp_c] = 1;
            swapIJKL(d,i,j,k,l);
            return 0;
        }
    }
    
    printf("You can only move diagnally\n");
    return -1;
    
}

int main()
{
	int r,c;
	int pr, pb;
	int i, k;
	char j, l;
	int d[ROWS][COLS]={
    {0,2,0,2,0,2,0,2},
    {2,0,2,0,2,0,2,0}, 
    {0,2,0,2,0,2,0,2}, 
    {1,0,1,0,1,0,1,0}, 
    {0,1,0,1,0,1,0,1}, 
    {3,0,3,0,3,0,3,0},
    {0,3,0,3,0,3,0,3},
	{3,0,3,0,3,0,3,0}};

    for(;;){
        // display board
        printDisplayFancy(d);
        // red turn
        while(1){
            printf("Red's turn: ");
            scanf("%d%c",&i,&j);
    	    printf("to: ");
        	scanf("%d%c",&k,&l);
        	//swapIJKL(d,i-1,j - 'a',k-1,l - 'a');
        	if(Playersturn(d, RED, i-1,j - 'a',k-1,l - 'a') == 0)
        	    break;
        	printf("Illegal move, try again\n");
        }
        
        //check for win
        
        //display board
        printDisplayFancy(d);
        //black turn
        while(1){
            printf("Canada's turn: ");
            scanf("%d%c",&i,&j);
    	    printf("to :");
        	scanf("%d%c",&k,&l);
        	//swapIJKL(d,i-1,j - 'a',k-1,l - 'a');
        	if(Playersturn(d, BLACK, i-1,j - 'a',k-1,l - 'a') == 0)
        	    break;
        	printf("Illegal move, try again\n");
        }
        
        //check for win
        
    }

	getchar();
	getchar();
    return 0;
}



/*


    if(player == RED){
        if(i - k == -1){
            if(j - l == 1 || j - l == -1){
                if(d[k][l]==EMPTY){
                    swapIJKL(d,i,j,k,l);
                    return 0;
                } else {
                    printf("Red must move to a empty location\n");
                    return -1;
                }
            }
        }
    } else { //BLACK
        if(i - k == 1){
            if(j - l == 1 || j - l == -1){
                if(d[k][l]==EMPTY){
                    swapIJKL(d,i,j,k,l);
                    return 0;
                } else {
                    printf("Black must move to a empty location\n");
                    return -1;
                }
            }
        }
    }
    
*/