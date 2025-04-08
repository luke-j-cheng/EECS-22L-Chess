#include <stdio.h> 
#include <string.h> 

//checks if user types quit or newgame returns 0 if neither, returns 1 if it's one or the other
int checkInput(char userinput[50]) { 
    int validInput = 0;
    validInput = ((strcmp(userinput, "new game\n")) == 0) || ((strcmp(userinput, "quit\n")) == 0);
    while (!validInput) {
        printf("Please enter 'new game' or 'quit' : \n"); 
        fgets(userinput, 50, stdin); 
        validInput = ((strcmp(userinput, "new game\n")) == 0) || ((strcmp(userinput, "quit\n")) == 0);
    }
    return validInput; 
}    
//prints the board/updated board
int printboard(char board[3][3]) {
    printf("3_%c_|_%c_|_%c_\n", board[0][0], board[0][1], board[0][2]);
    printf("2_%c_|_%c_|_%c_\n", board[1][0], board[1][1], board[1][2]);
    printf("1_%c_|_%c_|_%c_\n", board[2][0], board[2][1], board[2][2]);
    printf("  A   B   C ");
        printf("\n"); 
}

//Executes player move
int play(char board[3][3], int player) {
    int validMove = 1; 
    while (validMove){
        char gridIn[50]; 
        char column = '0'; 
        char row = '0'; 
        int quit = 0;
        printf("Player %d's Move: ", player); 
        fgets(gridIn,sizeof(gridIn), stdin);
        quit = (strcmp(gridIn, "quit\n"));
        if (quit == 0) {
            return 0; 
        }
        //Check if their input is valid
        if (((gridIn[0] - 'A') >= 0) && ((gridIn[0] - 'A') < 3) && (('3' - gridIn[1]) >= 0) && (('3' - gridIn[1]) < 3) && (gridIn[2] != '\0')) {
            column = (gridIn[0] - 'A');
            row = ('3' - gridIn[1]);
            //Reprompts if spot is already taken
            if ((board[row][column] == 'O') || (board[row][column] == 'X')) {
                printf("Spot is already taken, please try again\n");
                continue; 
            }
            //Places X if player1
            else if (player == 1) {
                board[row][column] = 'X';
            }
            //Places O if player2
            else if (player == 2) {
                board[row][column] = 'O';
            }
            break; 
        }    
        //Reprompts if their move isn't valid.
        else {
            printf("Invalid move, please specify both column and row.\n");
            continue; 
        }

    }
   return 1;
}
//Chekcs if a player has won
int checkWin(char board[3][3], int player) {
    char symbol; 
    if (player == 1) {
        symbol = 'X';
    }
    else {
        symbol = 'O';
    }
    //Checks Row
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == symbol) && (board[i][1] == symbol) && (board[i][2] == symbol)) {
            return 0; 
        }
    }
    //Checks Column
    for (int j = 0; j < 3; j++) {
        if ((board[0][j] == symbol) && (board[1][j] == symbol) && (board[2][j] == symbol)) {
            return 0; 
        }
    }
    //Checks Diagonals
    if (((board[0][0] == symbol) && (board[1][1] == symbol) && (board[2][2] == symbol)) || ((board[2][0] == symbol) && (board[1][1] == symbol) && (board[0][2] == symbol))) { 
            return 0; 
    }
    else {
        return 1; 
    }
}
int main() {
    int end = 1; 
    
    while (end) {
        int newgame = 0; 
        int count = 0; 
        char userinput[50]; //array to store userinput
        printf("Please enter 'new game' or 'quit' : \n");      
        fgets(userinput, sizeof(userinput), stdin); //Gets userinput to start new game or quit 
        //checks if they typed new game or quit
        if (checkInput(userinput)) {
            if (strcmp(userinput, "new game\n") == 0) {
                newgame = 1; 
            }
            else {
                newgame = 0;
                end = 0; 
            }
        }
        //Loops game
        while (newgame) {
            int player1 = 1; 
            int player2 = 2; 
            int winner = 0; 
            char board[3][3] = {
                {'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'} 
            } ;
            int gameend = 1; 
            //Loops until game is over
            while (gameend) {
                printboard(board); 
                gameend = play(board, player1); 
                if (gameend == 0) {
                    newgame = 0;
                    break; 
                }
                gameend = checkWin(board, player1);
                if (gameend == 0) {
                    printboard(board);
                    winner = 1; 
                    continue;  
                }
                printboard(board);
                int boardfull = 0;
                //Checks if board is full
                for (int i = 0; i < 3; i++) { 
                    for (int j = 0; j < 3; j++) {
                        if (board[i][j] != '_') {
                            boardfull = boardfull + 1; 
                        }
                    }
                }
                if (boardfull == 9) {
                    printf("No more valid moves\n");
                    newgame = 0;  
                    break;
                }

                gameend = play(board, player2); 
                if (gameend == 0) {
                    newgame = 0;
                    break; 
                }
                gameend = checkWin(board, player2);
                if (gameend == 0) {
                    printboard(board);
                    winner = 2; 
                    continue;
                }
                continue; 
            }
            if (winner == 1 || winner ==2) {
                printf("Congrats Player %d, You Win!\n", winner);     
                break; 
            }        
        }
        continue; 
    }
    printf("Ending Program...\n");
}
//EOF