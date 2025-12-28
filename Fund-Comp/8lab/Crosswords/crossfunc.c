// crossfunc.c
// Gabriel Marques
// Function program of crossword.c
#include "crossfunc.h"


void initBoard(char board[][MAX_BOARD_SIZE], char filling){
    for (int i = 0; i < MAX_BOARD_SIZE; i ++){
        for (int j = 0; j < MAX_BOARD_SIZE; j++){
            board[i][j] = filling;         
        }
    }
}

int readInfile(FILE *fp, char (*listPtr)[MAX_WORD_LENGTH], FILE *out){
    fprintf(out, "\n");
    int count = 0;
    char buf[BUFSIZ]; //an intermediate array to store and analyze one word with an "unlimited" size (BUFSIZ)


    while(!feof(fp)){

        if(count >= MAX_WORDS){
            fprintf(out, "Number of words was exceeded. Just the first %d words will be used.\n", MAX_WORDS);
            break; 
        }
        fgets(buf, BUFSIZ, fp);
        buf[strcspn(buf, "\n")] = '\0';
        //checks if it is the end of the file
        if(strcmp(buf, ".") == 0) break;

        //checks if it is in the right length
        if (strlen(buf) < MIN_WORD_LENGTH || strlen(buf) >= MAX_WORD_LENGTH) {
            fprintf(out, "Word number %d is not within the proper length: %s\n", count + 1, buf);
            continue;
        }
        
        //checks if all the characters and letters
        int flag = 0; //used to signal the detection of a non-letter char
        for (int i = 0; i < strlen(buf); i++) {
            if (!isalpha(buf[i])) {
                flag = 1;
                break;
            }
        }
        if (flag){
            fprintf(out, "A word with a non-letter character was found: %s\n", buf);
            continue;
        }

        //make it all upper case
        for (size_t i = 0; i < strlen(buf); i++) {
            buf[i] = toupper(buf[i]);
        }

        strcpy(listPtr[count], buf); 

        count++;
    }

    if(count < 2){
        fprintf(out, "Not enough words inputed!\n");
        return -1;
    }

    //sorting algorithm (bubble) in descending order of length here 
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strlen(listPtr[j]) < strlen(listPtr[j + 1])) {
                char temp[MAX_WORD_LENGTH];
                strcpy(temp, listPtr[j]);
                strcpy(listPtr[j], listPtr[j + 1]);
                strcpy(listPtr[j + 1], temp);
            }
        }
    }

    fprintf(out, "\nAll the words read: \n");
    return count;    
}

void printBoard(char board[][MAX_BOARD_SIZE], FILE *out){

    fprintf(out, "\n+");
    for (int i = 0; i < MAX_BOARD_SIZE; i++){
        fprintf(out, "-");
    }
    fprintf(out, "+");
    fprintf(out, "\n");
    
    for (int i = 0; i < MAX_BOARD_SIZE; i++){
        fprintf(out, "|");
        for (int j = 0; j < MAX_BOARD_SIZE; j++){
            fprintf(out, "%c", board[i][j]);
        }  
        fprintf(out, "|");
        fprintf(out, "\n");  
    }

    fprintf(out, "+");
    for (int i = 0; i < MAX_BOARD_SIZE; i++){
        fprintf(out, "-");
    }
    fprintf(out, "+");
    fprintf(out, "\n\n");
}

void scrambledWords(char words[][MAX_WORD_LENGTH], int count, FILE *out, WordAddedInfo Info[]){


    char buf[MAX_WORD_LENGTH];

    fprintf(out, "\nCLUES:\n");
    fprintf(out, "Location |  Direction | Anagram\n");
    for (int i = 0; i < count; i++) {
        int p1 = 0;
        int p2 = strlen(words[i]) - 1;
        int j = 0;

        while (p1 <= p2) {
            if (p1 == p2) {
                buf[j] = words[i][p1];
                j++;
                break;
            }
            buf[j++] = words[i][p2--];
            buf[j++] = words[i][p1++];
        }
        buf[j] = '\0'; // Null-terminate the scrambled word

        char direction[MAX_WORD_LENGTH];
        if(Info[i].position == 1){
            strcpy(direction, "Horizontal");
        } else if(Info[i].position == 0){
            strcpy(direction, "Vertical");
        }
        fprintf(out, "  %2d, 2%d | %10s | %s\n", Info[i].col, Info[i].row, direction, buf);
    }
    fprintf(out, "\n");
}

    
    

int wordsArrangement(char wordsList[][MAX_WORD_LENGTH], char fSolution[][MAX_BOARD_SIZE], char fPuzzle[][MAX_BOARD_SIZE], int count, WordAddedInfo wordsInfo[MAX_WORDS]) {


    int skippedWords[count];
    int numberSkipped = 0;

    int countWordsAdded = 0;
    initBoard(fSolution, SOLUTION_BOARD_FILLING);

    // Place the first word in the middle of the board
    int middleRow = MAX_BOARD_SIZE / 2;
    int wordLen = strlen(wordsList[0]);
    int startCol = (MAX_BOARD_SIZE - wordLen) / 2;
    for (int i = 0; i < wordLen; i++) {
        fSolution[middleRow][startCol + i] = wordsList[0][i];
    }
    wordsInfo[0].numberWord = 0;
    wordsInfo[0].row = middleRow;
    wordsInfo[0].col = startCol;
    wordsInfo[0].position = 1; // Horizontal
    countWordsAdded++;

    // Place the remaining words
    for (int i = 1; i < count; i++) { //i is teh index of the word to be added
        int placed = 0;
        for (int k = 0; k < strlen(wordsList[i]) && !placed; k++) {  //k is the index to of the letter of the word to be added
            for (int w = 0; w < countWordsAdded && !placed; w++) { // w loops through the words already added
                int prevWordIndex = wordsInfo[w].numberWord;
                int prevWordRow = wordsInfo[w].row;
                int prevWordCol = wordsInfo[w].col;
                int prevWordPos = wordsInfo[w].position;
                for (int j = 0; j < strlen(wordsList[prevWordIndex]) && !placed; j++) { // j loops through the letters of the words already added
                    if (wordsList[i][k] == wordsList[prevWordIndex][j]) {
                        int newRow, newCol, valid = 1;
                        if (prevWordPos == 1) { // Previous word is horizontal, so new word is vertical
                            newRow = prevWordRow - k;
                            newCol = prevWordCol + j;
                            int len = strlen(wordsList[i]);
                            if (newRow < 0 || newRow + len > MAX_BOARD_SIZE) {
                                valid = 0;
                            } else {
                                for (int l = 0; l < len; l++) {
                                    int r = newRow + l;
                                    int c = newCol;
                                    if (fSolution[r][c] != SOLUTION_BOARD_FILLING && fSolution[r][c] != wordsList[i][l]) {
                                        valid = 0;
                                        break;
                                    }
                                    // just  check neighbors if not the intersection
                                    if (l != k) {
                                        // first letter: check above, left, right
                                        if (l == 0) {
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // For last letter: check below, left, right
                                        else if (l == len - 1) {
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // Middle letters: check left and right
                                        else {
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        if (!valid) break;
                                    }
                                }
                            }
                        } else { // Previous word is vertical, so new word is horizontal
                            newRow = prevWordRow + j;
                            newCol = prevWordCol - k;
                            int len = strlen(wordsList[i]);
                            if (newCol < 0 || newCol + len > MAX_BOARD_SIZE) {
                                valid = 0;
                            } else {
                                for (int l = 0; l < len; l++) {
                                    int r = newRow;
                                    int c = newCol + l;
                                    if (fSolution[r][c] != SOLUTION_BOARD_FILLING && fSolution[r][c] != wordsList[i][l]) {
                                        valid = 0;
                                        break;
                                    }
                                    if (l != k) {
                                        // For first letter: check left, up, down
                                        if (l == 0) {
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // For last letter: check right, up, down
                                        else if (l == len - 1) {
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // Middle letters: check up and down
                                        else {
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        if (!valid) break;
                                    }
                                }
                            }
                        }
                        if (valid) {
                            for (int l = 0; l < strlen(wordsList[i]); l++) {
                                if (prevWordPos == 1) {
                                    fSolution[newRow + l][newCol] = wordsList[i][l];
                                } else {
                                    fSolution[newRow][newCol + l] = wordsList[i][l];
                                }
                            }
                            wordsInfo[countWordsAdded].numberWord = i;
                            wordsInfo[countWordsAdded].row = newRow;
                            wordsInfo[countWordsAdded].col = newCol;
                            wordsInfo[countWordsAdded].position = (prevWordPos == 1) ? 0 : 1;
                            countWordsAdded++;
                            placed = 1;
                        } 
                    }
                }
            }
        }
        if (!placed) {
            printf("\nThe word number %d was skipped!!\n", i+1);
            skippedWords[numberSkipped] = i;
            numberSkipped++;
        }

    }

    //go through the skipped words

    for (int i = 1; i < numberSkipped; i++) { //i is the index of the indexes stored in skipped words, which stored the index of the words skipped in wordLists
        int placed = 0;
        for (int k = 0; k < strlen(wordsList[skippedWords[i]]) && !placed; k++) {  //k is the index to of the letter of the word to be added
            for (int w = 0; w < countWordsAdded && !placed; w++) { // w loops through the words already added
                int prevWordIndex = wordsInfo[w].numberWord;
                int prevWordRow = wordsInfo[w].row;
                int prevWordCol = wordsInfo[w].col;
                int prevWordPos = wordsInfo[w].position;
                for (int j = 0; j < strlen(wordsList[prevWordIndex]) && !placed; j++) { // j loops through the letters of the words already added
                    if (wordsList[i][k] == wordsList[prevWordIndex][j]) {
                        int newRow, newCol, valid = 1;
                        if (prevWordPos == 1) { // Previous word is horizontal, so new word is vertical
                            newRow = prevWordRow - k;
                            newCol = prevWordCol + j;
                            int len = strlen(wordsList[skippedWords[i]]);
                            if (newRow < 0 || newRow + len > MAX_BOARD_SIZE) {
                                valid = 0;
                            } else {
                                for (int l = 0; l < len; l++) {
                                    int r = newRow + l;
                                    int c = newCol;
                                    if (fSolution[r][c] != SOLUTION_BOARD_FILLING && fSolution[r][c] != wordsList[skippedWords[i]][l]) {
                                        valid = 0;
                                        break;
                                    }
                                    // just  check neighbors if not the intersection
                                    if (l != k) {
                                        // first letter: check above, left, right
                                        if (l == 0) {
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // For last letter: check below, left, right
                                        else if (l == len - 1) {
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // Middle letters: check left and right
                                        else {
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        if (!valid) break;
                                    }
                                }
                            }
                        } else { // Previous word is vertical, so new word is horizontal
                            newRow = prevWordRow + j;
                            newCol = prevWordCol - k;
                            int len = strlen(wordsList[skippedWords[i]]);
                            if (newCol < 0 || newCol + len > MAX_BOARD_SIZE) {
                                valid = 0;
                            } else {
                                for (int l = 0; l < len; l++) {
                                    int r = newRow;
                                    int c = newCol + l;
                                    if (fSolution[r][c] != SOLUTION_BOARD_FILLING && fSolution[r][c] != wordsList[skippedWords[i]][l]) {
                                        valid = 0;
                                        break;
                                    }
                                    if (l != k) {
                                        // For first letter: check left, up, down
                                        if (l == 0) {
                                            if (c - 1 >= 0 && fSolution[r][c - 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // For last letter: check right, up, down
                                        else if (l == len - 1) {
                                            if (c + 1 < MAX_BOARD_SIZE && fSolution[r][c + 1] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        // Middle letters: check up and down
                                        else {
                                            if (r - 1 >= 0 && fSolution[r - 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                            if (r + 1 < MAX_BOARD_SIZE && fSolution[r + 1][c] != SOLUTION_BOARD_FILLING) valid = 0;
                                        }
                                        if (!valid) break;
                                    }
                                }
                            }
                        }
                        if (valid) {
                            for (int l = 0; l < strlen(wordsList[skippedWords[i]]); l++) {
                                if (prevWordPos == 1) {
                                    fSolution[newRow + l][newCol] = wordsList[skippedWords[i]][l];
                                } else {
                                    fSolution[newRow][newCol + l] = wordsList[skippedWords[i]][l];
                                }
                            }
                            wordsInfo[countWordsAdded].numberWord = i;
                            wordsInfo[countWordsAdded].row = newRow;
                            wordsInfo[countWordsAdded].col = newCol;
                            wordsInfo[countWordsAdded].position = (prevWordPos == 1) ? 0 : 1;
                            countWordsAdded++;
                            placed = 1;
                        } 
                    }
                }
            }
        }

    }


    

    
    // Copy the solution board to the puzzle board, replacing letters with PUZZLE_BOARD_FILLING
    for (int i = 0; i < MAX_BOARD_SIZE; i++) {
        for (int j = 0; j < MAX_BOARD_SIZE; j++) {
            if (fSolution[i][j] != SOLUTION_BOARD_FILLING) {
                fPuzzle[i][j] = ' ';
            } else {
                fPuzzle[i][j] = PUZZLE_BOARD_FILLING;
            }
        }
    }
    return countWordsAdded;
}

