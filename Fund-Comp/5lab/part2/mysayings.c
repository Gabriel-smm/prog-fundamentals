// Gabriel Marques
// mysayings.c
// This program prompts the user to store, display, add and save user's favorite sayings
#include <stdio.h>
#include <string.h>
#include <ctype.h>

const int STR_MAXLEN = 256;
const int MAX_SAYINGS = 50;

int displayMenu();
int readFile(FILE *fp, char sayings[][STR_MAXLEN]);
void cleanup(char str[]);

int main(){
    
    int i;
    char infile[30];
    FILE *fp;
    int userChoice;

    
    //checking file used
    printf("\n");
    printf("enter the data file name: ");
    scanf("%s", infile);

    fp = fopen(infile, "r+");
    if(!fp){
        printf("This file %s can't be read! The program ends here.\n", infile);
        return 1;
    } else {
      char sayings[MAX_SAYINGS][STR_MAXLEN];
      int count = readFile(fp, sayings);

        while(1){
          userChoice = displayMenu();

          switch ((int) userChoice){
          case 1:
            printf("\n\nThose are the sayings saved in the %s:\n\n", infile);
            for (int n = 0; n < count; n++) {
             printf("%s\n", sayings[n]);
            }            
            break;

          case 2: {
            char newSaying[STR_MAXLEN];
            printf("\nEnter the new saying: ");
            getchar(); //consumes the new line left after entering the number to the last scanf, character which woul enter the fgets function.
            fgets(newSaying, STR_MAXLEN, stdin);
            if(strlen(newSaying) > 256){
              printf("Invalid string lenght!");
              break;
            }
            cleanup(newSaying);
            strcpy(sayings[count], newSaying);
            count++;
            break;
          }

          case 3:{
            char schSaying[STR_MAXLEN];
            printf("\nEnter the substring: ");
            getchar(); //consumes the new line left after entering the number to the last scanf, character which woul enter the fgets function.
            fgets(schSaying, STR_MAXLEN, stdin);
            if(strlen(schSaying) > 256){
              printf("Invalid string lenght!");
              break;
            }
            cleanup(schSaying);
            int countFound = 0;
            printf("\n");
            printf("\nThose are the sayings that cointain this substring: \n");
            for (i = 0; i < count; i++){
              if (strstr(sayings[i], schSaying)){
                printf("%s\n", sayings[i]);
                countFound++;
              }              
            }
            if (countFound == 0) printf("No string found\n");  
            break;
          }
          case 4:{
            char newInfile[30];
            FILE *newFp;

            printf("\n");
            printf("enter the data file name (with .txt in the end): ");
            scanf("%s", newInfile);

            newFp = fopen(newInfile, "w");
            if (!newFp) {
               printf("This file %s can't be written!\n", newInfile);
               break;
            }

            for (i = 0; i < count; i++){
              fprintf(newFp, "%s\n", sayings[i]);
            }
            
            break;
          }
          case 5:
            printf("\nThank you! Bye! \n");
            break;
          
          default:
            printf("\nThat's not a valid choice!!\n\n");
            break;
          }
          if (userChoice == 5) break; 
          
        }
      
      }

    return 0;
}

int displayMenu (){
    int x;
    printf("\n1. Display all sayings currently in the database\n");
    printf("2. Enter a new saying into the database\n");
    printf("3. List sayings that contain a given substring entered by the user\n");
    printf("4. Save all sayings in a new text file\n");
    printf("5. Quit the program");

    printf("\n\nEnter your choice: ");
    scanf("%d", &x);
    return x;

}

int readFile(FILE *fp, char sayings[][STR_MAXLEN]){

  char Temp_array[STR_MAXLEN];
  int n = 0;

  while (1) {
    fgets(Temp_array, STR_MAXLEN, fp);
    if (feof(fp)) break;
    cleanup(Temp_array);
    strcpy(sayings[n], Temp_array);
    n++;
  }

  return n;
}

void cleanup(char str[]){
  str[strlen(str)-1] = '\0';
}
