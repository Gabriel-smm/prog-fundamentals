// crosswords.c
// Gabriel Marques
// this program creates a crossword game based on the given words.

#include "crossfunc.h"

int main (int argc, char *argv[]){

    //initializes both boards
    Board puzzleBoard;
    Board solutionBoard;
    
    puzzleBoard.boardFilling = PUZZLE_BOARD_FILLING;
    solutionBoard.boardFilling = SOLUTION_BOARD_FILLING;

    initBoard(puzzleBoard.board, puzzleBoard.boardFilling);
    initBoard(solutionBoard.board, solutionBoard.boardFilling);



    //reading file

    if (argc == 1){
        FILE *fp;
        char infile[30]; 
        char listWords[MAX_WORDS][MAX_WORD_LENGTH];
        int userChoice;
        int count;

        printf("\n\nEnter one (1) to manually input and zero (0) to input a file: ");
        scanf("%d", &userChoice);

        if(userChoice == 1){
            count = 0;
            char userWord[MAX_WORD_LENGTH];

            while(count < 20){
                printf("\nEnter the word number %d: ", count + 1);
                scanf("%s", userWord);

                if (!strcmp(userWord, ".")){
                    break;                    
                }

                //checks the lenght of the string
                if (strlen(userWord) < MIN_WORD_LENGTH || strlen(userWord) >= MAX_WORD_LENGTH) {
                printf("\nWord number %d is needs to be within the proper length!\n", count + 1);
                continue;
                }
            

                //checks if all the characters and letters
                int flag = 0; //used to signal the detection of a non-letter char
                for (int i = 0; i < strlen(userWord); i++) {
                    if (!isalpha(userWord[i])) {
                        flag = 1;
                        break;
                    }
                }
                if (flag){
                    printf("\nYou cannot input words with non-letter characters: %s\n", userWord);
                    continue;
                }

                //make it all upper case
                for (size_t i = 0; i < strlen(userWord); i++) {
                    userWord[i] = toupper(userWord[i]);
                }

                strcpy(listWords[count], userWord);

                count++;
            }

            if(count < 2){
                printf("Not enough words inputed!");
                return -1;
            }

            for (int i = 0; i < count - 1; i++) {
                for (int j = 0; j < count - i - 1; j++) {
                    if (strlen(listWords[j]) < strlen(listWords[j + 1])) {
                        char temp[MAX_WORD_LENGTH];
                        strcpy(temp, listWords[j]);
                        strcpy(listWords[j], listWords[j + 1]);
                        strcpy(listWords[j + 1], temp);
                    }
                }
            }

        } else if (userChoice == 0) {
            printf("\n\nEnter the starter file name: ");
            scanf("%s", infile);

            fp = fopen(infile, "r");

            if(!fp){
                printf("\nFile not found!\n");
                return 1;
            }

            printf("\n\n Crossword Puzzle Generator\n");
            printf("----------------------------\n");
            count = readInfile(fp, listWords, stdout);
            for (int i = 0; i < count; i++){
                printf("%s\n", listWords[i]);
            }
        }


        
        WordAddedInfo wordsInfo[MAX_WORDS];
        int wordsAdded = wordsArrangement(listWords, solutionBoard.board, puzzleBoard.board, count, wordsInfo);
        printf("\n\nPuzzle board:\n");
        printBoard(puzzleBoard.board, stdout);
        printf("\nSolution board:\n");
        printBoard(solutionBoard.board, stdout);

        char wordListAdded[MAX_WORDS][MAX_WORD_LENGTH];
        for (int i = 0; i < wordsAdded; i++){
            strcpy(wordListAdded[i], listWords[wordsInfo[i].numberWord]);
        }
        

        scrambledWords(wordListAdded, wordsAdded, stdout, wordsInfo);

        
        
        
    } else if (argc == 2){ //user enters the starter file in the command line
        //will be used to use a file in the command line
        FILE *fp;
        char listWords[MAX_WORDS][MAX_WORD_LENGTH];

        fp = fopen(argv[1], "r");

        if(!fp){
            printf("\nFile not found!\n");
            return 1;
        }

        //printing section
        printf("\n\n Crossword Puzzle Generator\n");
        printf("----------------------------\n");
        int count = readInfile(fp, listWords, stdout);
        for (int i = 0; i < count; i++){
            printf("%s\n", listWords[i]);
        }
        
        WordAddedInfo wordsInfo[MAX_WORDS];
        int wordsAdded = wordsArrangement(listWords, solutionBoard.board, puzzleBoard.board, count, wordsInfo);
        printf("\n\nPuzzle board:\n");
        printBoard(puzzleBoard.board, stdout);
        printf("\nSolution board:\n");
        printBoard(solutionBoard.board, stdout);

        char wordListAdded[MAX_WORDS][MAX_WORD_LENGTH];
        for (int i = 0; i < wordsAdded; i++){
            strcpy(wordListAdded[i], listWords[wordsInfo[i].numberWord]);
        }
        

        scrambledWords(wordListAdded, wordsAdded, stdout, wordsInfo);


    } else if (argc == 3){ //user enters bothe the starter file and output file in the command line
        //will be used to input an input and output file
        FILE *fpi; 
        FILE *fpo; 

        char listWords[MAX_WORDS][MAX_WORD_LENGTH];

        fpi = fopen(argv[1], "r");
        fpo = fopen(argv[2], "w");

        if(!fpi){
            printf("\nInput file not found!\n");
            return 1;
        }
        

        //printing section
        fprintf(fpo, "\n\n Crossword Puzzle Generator\n");
        fprintf(fpo, "----------------------------\n");
        fprintf(fpo, "\nAll the words read: \n");
        int count = readInfile(fpi, listWords, fpo);
        for (int i = 0; i < count; i++){
            fprintf(fpo, "%s\n", listWords[i]);
        }
        
        
        WordAddedInfo wordsInfo[MAX_WORDS];
        int wordsAdded = wordsArrangement(listWords, solutionBoard.board, puzzleBoard.board, count, wordsInfo);
        fprintf(fpo, "\n\nPuzzle board:\n");
        printBoard(puzzleBoard.board, fpo);
        fprintf(fpo, "\nSolution board:\n");
        printBoard(solutionBoard.board, fpo);

        char wordListAdded[MAX_WORDS][MAX_WORD_LENGTH];
        for (int i = 0; i < wordsAdded; i++){
            strcpy(wordListAdded[i], listWords[wordsInfo[i].numberWord]);
        }
        

        scrambledWords(wordListAdded, wordsAdded, fpo, wordsInfo);

        


    } else {
        printf("\nToo many arguments in the command line!\n");
    }
    

    
    return 0;
}
