//usastates.c
//gabriel marques

#include "statesfunc.h"

int main (){

FILE *fp;
char infile[30];
States statesData[MAX_STATES];

printf("\n\nEnter the starter file name: ");
scanf("%s", infile);

fp = fopen(infile, "r");

if(!fp){
    printf("\nFile not found!\n");
    return 1;
} else {
    int amountStates = storeData(fp, statesData);
    int userChoice;
    int loopFlag = 1;

    while (loopFlag){
        printOptions();
        printf("\nEnter you choice: ");
        scanf("%d", &userChoice);
        switch (userChoice){
            case 1:
                displayData(statesData, amountStates);
                break;

            case 2:{
                char abrevChosen[3];
                getchar();
                printf("\nEnter state's abbreviation (2 letters): "); //assuming that the user will enter a valid and correct input
                fgets(abrevChosen, sizeof(abrevChosen), stdin);       //cleaning user's entry
                abrevChosen[strcspn(abrevChosen, "\n")] = '\0';
                for(int i = 0; i < amountStates; i++){
                    if (strcasecmp(statesData[i].abrev, abrevChosen) == 0){
                        printf("\n%s\n", statesData[i].capital);
                        break;
                    } else if (i == amountStates - 1) {
                        printf("\nNo state found.\n");
                    }
                    
                }
                break;
            }

            case 3:{
                char abrevChosen[3];
                getchar();
                printf("\nEnter state's abbreviation (2 letters): "); //assuming that the user will enter a valid and correct input
                fgets(abrevChosen, sizeof(abrevChosen), stdin);       //cleaning user's entry
                abrevChosen[strcspn(abrevChosen, "\n")] = '\0';
                for(int i = 0; i < amountStates; i++){
                    if (strcasecmp(statesData[i].abrev, abrevChosen) == 0){
                        printf("\n%d\n", statesData[i].year);
                        break;
                    } else if (i == amountStates - 1) {
                        printf("\nNo state found.\n");
                    }
                    
                }
                break;
            }
            
            case 4:{
                char abrevChosen[3];
                getchar();
                printf("\nEnter state's abbreviation (2 letters): "); //assuming that the user will enter a valid and correct input
                fgets(abrevChosen, sizeof(abrevChosen), stdin);       //cleaning user's entry
                abrevChosen[strcspn(abrevChosen, "\n")] = '\0';
                for(int i = 0; i < amountStates; i++){
                    if (strcasecmp(statesData[i].abrev, abrevChosen) == 0){
                        printf("\n%.*s | %.*s | %4d\n", MAX_NAMELEN, statesData[i].name, MAX_NAMELEN, statesData[i].capital, statesData[i].year);
                        break;
                    } else if (i == amountStates - 1) {
                        printf("\nNo state found.\n");
                    }
                    
                }
                break;
            }

            case 5:{
                int userYear;
                int counter = 0;
                printf("\nEnter the year of entry: ");
                scanf("%d", &userYear);
                for(int i = 0; i < amountStates; i++){
                    if (userYear <= statesData[i].year){
                        printf("\n%.*s, %4d\n", MAX_NAMELEN, statesData[i].name, statesData[i].year);
                        counter++;
                    }                    
                }

                if (counter == 0) {
                        printf("\nNo state found.\n");
                }

                break;
            }
                
            case 6:
                loopFlag = 0;
                printf("\nThank you! Bye!\n");
                break;
            
            default:
                printf("\nInvalid input!\n");
                break;
        }
    }


}

return 0;
}
