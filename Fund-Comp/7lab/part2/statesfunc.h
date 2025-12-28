//usafunc.h
//Gabriel Marques
//This program is designed to, based on a starter data about US states, provide the user options to explore US state's information

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STATES 100 //allows easy portability to data from other countries
#define MAX_NAMELEN 15 //allows different countries to uptade to their state with max lenght

typedef struct {
    char abrev[3];
    char name[MAX_NAMELEN];
    char capital[MAX_NAMELEN];
    int year;
} States;

int storeData(FILE *fp, States statesData[]);
void displayData(States statesData[], int count);
void printOptions();
