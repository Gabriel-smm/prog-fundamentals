// crossfunc.h
// Gabriel Marques
// header of crossword

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BOARD_SIZE 15
#define PUZZLE_BOARD_FILLING '#'
#define SOLUTION_BOARD_FILLING '.'
#define MAX_WORDS 20
#define MAX_WORD_LENGTH 16 //max length for a word + \0
#define MIN_WORD_LENGTH 2


void initBoard(char board[][MAX_BOARD_SIZE], char filling);
int readInfile(FILE *fp, char (*listPtr)[MAX_WORD_LENGTH], FILE *out);
void printBoard(char board[][MAX_BOARD_SIZE], FILE *out);

typedef struct { //used to store information about the words added to the crossword puzzle
    int numberWord;
    int row;      // coordinates of the first letter  
    int col;
    int position; // 0 for vertical, 1 for horizontal
} WordAddedInfo;

void scrambledWords(char words[][MAX_WORD_LENGTH], int count, FILE *out, WordAddedInfo Info[]);
int wordsArrangement(char wordsList[][MAX_WORD_LENGTH], char fSolution[][MAX_BOARD_SIZE], char fPuzzle[][MAX_BOARD_SIZE], int count, WordAddedInfo wordsInfo[MAX_WORDS]);

typedef struct{
    char board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char boardFilling;
} Board;


