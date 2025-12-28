#include "lifefunc.h"

void addCell(char board[][MAX], int x, int y){
    board[y][x] = ALIVE;
}

void removeCell(char board[][MAX], int x, int y){
    board[y][x] = DEAD;
}

void initBoard(char board[][MAX]){
    for (int i = 0; i < MAX; i ++){
        for (int j = 0; j < MAX; j++){
            board[i][j] = BLANK;         
        }
    }
}

void displayBoard(char board[][MAX]){

    printf("\n+");
    for (int i = 0; i < MAX; i++){
        printf("-");
    }
    printf("+");
    printf("\n");
    
    for (int i = 0; i < MAX; i++){
        printf("|");
        for (int j = 0; j < MAX; j++){
            printf("%c", board[i][j]);
        }  
        printf("|");
        printf("\n");  
    }

    printf("+");
    for (int i = 0; i < MAX; i++){
        printf("-");
    }
    printf("+");
    printf("\n");

}


int isValid(int x, int y){
   return ( !(x < 0 || x >= MAX || y < 0 || y >= MAX) );
}


int countLiveNeighbors(char board[][MAX], int x, int y)
{
  int neighbors = 0;

  for (int a = y-1; a <= y+1; a++) {
    for (int b = x-1; b <= x+1; b++) {
      if (a == y && b == x) continue;
      if(board[a][b] == ALIVE && isValid(a,b) ) neighbors++;
    }
  }

  return neighbors;
}

