//Gabriel Marques
//ndfootball.c for lab4
//This program is supposed to display the chosen option of statistics for the Notre Dame Football fighting Irish. 


#include <stdio.h>
#include <math.h>

void showMenu();
void option1(int wins[], int losses[], int sizeAllGames);
void option2(int losses[], int sizeAllGames);
void option3(int wins[], int sizeAllGames);
void option4(int wins[], int losses[], int sizeAllGames);
void option5(int wins[],int losses[], int sizeAllGames);

int main(){

    int wins[] = 
 { 6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4, 6,
   7, 7, 6, 7, 8, 6, 3, 9, 9, 10, 8, 9,
   10, 7, 9, 7, 5, 9, 10, 6, 6, 3, 6, 7, 
   6, 6, 8, 7, 7, 8, 7, 9, 8, 7, 8, 9,
   9, 10, 4, 7, 7, 9, 9, 8, 2, 7, 6, 5, 
   2, 5, 5, 2, 9, 7, 9, 8, 7, 8, 10, 8, 
   8, 11, 10, 8, 9, 11, 9, 7, 9, 5, 6, 7, 
   7, 5, 5, 8, 12, 12, 9, 10, 10, 11, 6, 9, 
   8, 7, 9, 5, 9, 5, 10, 5, 6, 9, 10, 3, 
   7, 6, 8, 8, 12, 9, 8, 10, 4, 10, 12, 11, 
   10, 11, 9, 10, 14 };

    int losses[] = 
 { 3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1, 0,
   0, 0, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1,
   0, 2, 1, 1, 4, 0, 0, 2, 2, 5, 3, 1,
   2, 2, 1, 2, 2, 0, 2, 1, 2, 2, 0, 0,
   0, 0, 4, 2, 2, 0, 1, 2, 8, 3, 4, 5,
   8, 5, 5, 7, 1, 2, 0, 2, 2, 2, 1, 2,
   3, 0, 2, 3, 3, 1, 3, 4, 2, 6, 4, 5,
   5, 6, 6, 4, 0, 1, 3, 3, 1, 1, 5, 3,
   3, 6, 3, 7, 3, 6, 3, 7, 6, 3, 3, 9,
   6, 6, 5, 5, 1, 4, 5, 3, 8, 3, 1, 2,
   2, 2, 4, 3, 2 };

    int userChoice;
    int loopFlag = 1;
    int sizeAllGames = sizeof(wins)/sizeof(int);

    printf("\nWelcome to Fighting Irish Stats Finder!\n\n");

    while(loopFlag){
        showMenu();
        scanf("%d", &userChoice);
        switch (userChoice){
            case 1:
                option1(wins, losses, sizeAllGames);
                break;
            case 2:
                option2(losses, sizeAllGames);
                break;
            case 3:
                option3(wins, sizeAllGames);
                break;
            case 4:
                option4(wins, losses, sizeAllGames);
                break;
            case 5:
                option5(wins, losses, sizeAllGames);
                break;
            case 6:
                loopFlag = 0;
                printf("\nThank you! Bye!\n\n");
                break;
            default:
                printf("\nThat is not an option. Please, try again.\n");
                break;
            }
        }
    
    return 0;
}

void showMenu(){
    printf("\n1: display the record for a given year. \n");
    printf("2: display years with at least \"n\" losses.\n");
    printf("3: display years with at least \"n\" wins.\n");
    printf("4: display records from this year until a given year.\n");
    printf("5: display the year with at least \"m\" wins and \"n\" losses.\n");
    printf("6: exit\n");
    printf("\nEnter the choice: ");
}

void option1(int wins[], int losses[], int sizeAllGames){
    
    int year;
    printf("\nChoose a year: ");
    scanf("%d", &year);
    if(year - 1900 < 0 || year - 1900 > sizeAllGames){
        printf("\nThis year is not valid, try again!\n");
    } else {
        int Wins = wins[year-1900];
        int Losses = losses[year-1900];
        printf("Wins: %d, Losses: %d\n", Wins, Losses);
    }

}

void option2(int losses[], int sizeAllGames){
    
    int UserChoice;
    printf("\nChoose a minimum number for losses: ");
    scanf("%d", &UserChoice);
    if(UserChoice < 0){
        printf("\nNegative losses doesn't exist!\n");
    } else {
        printf("\nYears with at least %d losses: ", UserChoice);
        int count = 0;
        for (int i = 0; i < sizeAllGames; i++){
            if(losses[i] >= UserChoice){
                printf("%d ", i + 1900);
                count++;
            }
        }
        if (count == 0) printf("\nNo game with %d losses was found.\n", UserChoice);
        printf("\n");
    }

}

void option3(int wins[], int sizeAllGames){
    
    int UserChoice;
    printf("\nChoose a minimum number for wins: ");
    scanf("%d", &UserChoice);
    if(UserChoice < 0){
        printf("\nNegative wins doesn't exist!\n");
    } else {
        printf("\nYears with at least %d wins: ", UserChoice);
        int count = 0;
        for (int i = 0; i < sizeAllGames; i++){
            if(wins[i] >= UserChoice){
                printf("%d ", i + 1900);
                count++;
            }
        }
        if (count == 0) printf("\nNo game with %d wins was found.\n", UserChoice);
        printf("\n");
    }

}

void option4(int wins[], int losses[], int sizeAllGames){
    int year;
    printf("\nChoose some year before %d: ", (sizeAllGames+1899));
    scanf("%d", &year);
    if (year < 1900 || year > sizeAllGames + 1899) {
        printf("That is not a valid year (1900 >= year chosen >= current year).\n");
    } else {
        printf("Years   Wins   Losses  \n");
        for(int i = (year - 1900); i <= sizeAllGames-1; i++){
            printf("%5d", i + 1900);
            printf("   %4d   %6d\n", wins[i], losses[i]);
        }
    }

}

void option5(int wins[],int losses[], int sizeAllGames){
    
    int ChoiceWins;
    printf("\nChoose a minimum number for wins: ");
    scanf("%d", &ChoiceWins);
    int ChoiceLosses;
    printf("\nChoose a minimum number for losses: ");
    scanf("%d", &ChoiceLosses);

    if(ChoiceWins < 0 || ChoiceLosses < 0){
        printf("\nNegative losses or wins doesn't exist!\n");
    } else {
        printf("\nYears with at least %d wins and %d losses: ", ChoiceWins, ChoiceLosses);
        int count = 0;
        for (int i = 0; i < sizeAllGames; i++){
            if(wins[i] >= ChoiceWins && losses[i] >= ChoiceLosses){
                printf("%d ", i + 1900);
                count++;
            }
        }
        if (count == 0) printf("\nNo game with %d wins and %d losses was found.\n", ChoiceWins, ChoiceLosses);
        printf("\n");
    }
}



