#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX 40
#define ALIVE 'X'
#define DEAD ' '
#define BLANK ' '


void addCell(char board[][MAX], int x, int y);
void removeCell(char board[][MAX], int x, int y);
void initBoard(char board[][MAX]);
void displayBoard(char board[][MAX]);
int isValid(int x, int y);
int countLiveNeighbors(char board[][MAX], int x, int y);
    
