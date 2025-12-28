//statesfunc.c
//gabriel marques

#include "statesfunc.h"

int storeData(FILE *fp, States statesData[]){
    int count = 0;  //number of states read
    char arr[80];   // temporary array to read a line

    while (1){
        fgets(arr, 80, fp);
        if(feof(fp)) break;
        strcpy(statesData[count].abrev, strtok(arr, ","));
        strcpy(statesData[count].name, strtok(NULL, ","));
        strcpy(statesData[count].capital, strtok(NULL, ","));
        statesData[count].year = atoi(strtok(NULL, "\n"));
        count++;
    }
    return count;

}

void printOptions(){
    printf("\n");
    printf("Enter the number corresponding to the option of your choice: \n");
    printf("1 - Print all the data\n");
    printf("2 - Display state's capital based on the inputed abbreviation\n");
    printf("3 - Display state's year of entry as an US state based on the inputed abbreviation\n");
    printf("4 - Display state's information based on inputed abbreviation\n");
    printf("5 - List all the states that joined together after the chosen year\n");
    printf("6 - quit\n");
}



// this function was used to debug the proccess of collecting data
void displayData(States statesData[], int count){
    printf("\n");
    for (int i = 0; i < count; i++) {
        printf("  %2s | %20s | %20s | %4d \n", statesData[i].abrev, statesData[i].name, statesData[i].capital, statesData[i].year);
    }
}
