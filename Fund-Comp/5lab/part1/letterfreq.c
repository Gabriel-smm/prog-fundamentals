// Gabriel Marques
// letterfreq.c
// This program computes the frequency of characters in a given text file
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){

    const int f = 26;
    int frequency[f];
    for (int i = 0; i < f; i++) frequency[i] = 0;

    int i;
    int totalChar = 0;
    int totalLetter = 0;

    char infile[30];
    FILE *fp;


    printf("\n");
    printf("enter the data file name: ");
    scanf("%s", infile);

    fp = fopen(infile, "r");
    if(!fp){
        printf("This file %s can't be read!\n", infile);
        return 1;
    }


    //verification loop
    int x;
    while((x = fgetc(fp)) != EOF){
        x = tolower(x);
        for(i = 97; i < 123; i++){
            if(x == i) frequency[i-97] += 1;
        }
        totalChar += 1;
        if (x >= 97 && x <= 122) totalLetter += 1;
    }


    //printing 

    printf("\nSummary of the statistics for %s:\n\n", infile);
    
    printf("The total number of characters is %d\n", totalChar);
    printf("The total number of letters is %d\n\n", totalLetter);


    printf("Number's frequency:\n");
    for (i = 1; i < f+1; i++){
        int a = 97;
        printf("%c:%7d  ", a+i-1, frequency[i-1]);
        if(i % 6 == 0) printf("\n");
    }
    
    printf("\n\n");

    printf("Number's percentage:\n");
    for (i = 1; i < f+1; i++){
        int a = 97;
        double percentage = (double) frequency[i-1] / totalLetter * 100;
        printf("%c:%7.1lf%%  ", a+i-1, percentage);
        if(i % 6 == 0) printf("\n");
    }

    printf("\n\n");

    return 0;
}
