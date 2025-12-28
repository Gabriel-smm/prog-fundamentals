#include "lifefunc.h"

int main (int argc, char *argv[]){
    char userChoice;
    int x,y;
    char board[MAX][MAX];
      
    initBoard(board);
    displayBoard(board);

        
    if(argc == 2){
       FILE *fp;
       fp = fopen(argv[1], "r");
       while(1){
       fscanf(fp, "%c", &userChoice);
       if (userChoice == 'a' || userChoice == 'r') {
          fscanf(fp, "%d %d", &x, &y);
          if (isValid(x,y)) {
             if (userChoice == 'a') addCell(board, x, y);
             if (userChoice == 'r') removeCell(board, x, y);
             system("clear");
             displayBoard(board);
          } else {
             printf("Those coordinates are out of bounds!\n");
          }
       } else if (userChoice == 'p'){
	 while(1){
             int count;
             char tempArray[MAX][MAX];
             for (int i = 0; i < MAX; i ++){
                for (int j = 0; j < MAX; j++){
                   tempArray[i][j] = BLANK;
                }
             }



          for(int i = 0; i < MAX; i++){
             for(int j = 0; j < MAX; j++){
               count = countLiveNeighbors(board, j, i);
               if(board[i][j] == ALIVE) {
                  if (count == 2 || count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;
               } else {
                  if (count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;
               }
            }
         }
          for (int i = 0; i < MAX; i++){
             for (int j = 0; j < MAX; j++){
                board[i][j] = tempArray[i][j];
             }
          }


         displayBoard(board);
         usleep(100000);
         }

        }
        
       }

    } else if (argc == 1){
      while(1) {

       printf("Choose an action: ");
       scanf("%c", &userChoice);
       if (userChoice == 'a' || userChoice == 'r') {
          scanf("%d %d", &x, &y);
          if (isValid(x,y)) {
             if (userChoice == 'a') addCell(board, x, y);
             if (userChoice == 'r') removeCell(board, x, y);
	     system("clear");
             displayBoard(board);
          } else {
             printf("Those coordinates are out of bounds!\n");
          }
          getchar();
       } else if (userChoice == 'n') {
         getchar();
	 int count;
	 char tempArray[MAX][MAX];
	 for (int i = 0; i < MAX; i ++){
            for (int j = 0; j < MAX; j++){
               tempArray[i][j] = BLANK;
            }
         }



         for(int i = 0; i < MAX; i++){
            for(int j = 0; j < MAX; j++){
               count = countLiveNeighbors(board, j, i);         
	       if(board[i][j] == ALIVE) {
                  if (count == 2 || count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;
               } else { 
                  if (count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;  
	       }
	    }
	 }
	 for (int i = 0; i < MAX; i++){
            for (int j = 0; j < MAX; j++){
               board[i][j] = tempArray[i][j];
	   }
	 }

	 
	 displayBoard(board);


       } else if (userChoice == 'p'){ 
          getchar();
	  while(1){
	     int count;
             char tempArray[MAX][MAX];
             for (int i = 0; i < MAX; i ++){
                for (int j = 0; j < MAX; j++){
                   tempArray[i][j] = BLANK;
                }
             }



          for(int i = 0; i < MAX; i++){
             for(int j = 0; j < MAX; j++){
               count = countLiveNeighbors(board, j, i);
               if(board[i][j] == ALIVE) {
                  if (count == 2 || count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;
               } else {
                  if (count == 3) tempArray[i][j] = ALIVE;
                  else tempArray[i][j] = DEAD;
               }
            }
         }
          for (int i = 0; i < MAX; i++){
             for (int j = 0; j < MAX; j++){
                board[i][j] = tempArray[i][j];
             }
          }


         displayBoard(board);
	 usleep(100000);
	 }

	
       } else if (userChoice == 'q') {
	  printf("\nThank you! Bye!\n");
          break;
       } else {
          printf("\nInvalid input!\n");
          getchar();
       }
      }
     }else{
	printf("\ninvalid entry\n");
     }


    return 0;

}


