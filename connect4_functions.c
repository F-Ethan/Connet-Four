/******************************************************************************
*
* File name: connect4_functions.c
*
* Author:  Ivan John Simon Ferrier
*          A14151920
*          iferrier@ucsd.edu
*
*
*     Lab #: 4
* Problem #: 1
*
******************************************************************************/


/*-----------------------------------------------------------------------------
   Include files
-----------------------------------------------------------------------------*/
#include "connect4_functions.h"

// If you would like to use standard library functions other than those
// declared in <stdio.h>, <stdlib.h>, <time.h>, <stdbool.h> (for which
// the #include directives are already given in connect4_functions.h),
// you may #include the corresponding header files here.



/*=============================================================================
  Constants and definitions
=============================================================================*/

// If you would like to define constants other than BOARD_SIZE_HORIZ and
// BOARD_SIZE_VERT, or if you would like to define new types, you may put
// the corresponding #defines and typedefs here.



/*=============================================================================
  Global variables
=============================================================================*/

// If you would like to use global variables, declare them here.




/*=============================================================================
  Forward function declarations
=============================================================================*/

// If you would like to use functions other than those already declared in
// connect4_functions.h, put the forward declarations of these functions here.

void undo_move(int board[][BOARD_SIZE_VERT], int m);


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

                Function Definitions of Required Functions

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/


/******************************************************************************
*                                                                             *
*                       Function print_welcome()                              *
*                                                                             *
******************************************************************************/
int print_welcome(void)
{
    srand(time(0));  // standard initialization of srand
    printf("*** Welcome to the Connect Four game!!! ***\nWould you like to make the first move [y/n]: \n");
    char c;
    scanf("%c", &c);
    while (getchar() != '\n'); // clears the buffer past the first char

    if(c == 'n' | c == 'N'){ // n or N  makes it so that the computer goes first
        return 2;
    }
    // anything else will have the user go first
    return 1;
}

/******************************************************************************
*                                                                             *
*                      Function display_board()                               *
*                                                                             *
******************************************************************************/
void display_board(int board[][BOARD_SIZE_VERT])
{
    printf("\n");
    // for each row
    for(int i = 0; i< BOARD_SIZE_VERT;i++){

        //print one line of the boxes that makes up the board
        for( int j= 0; j<BOARD_SIZE_HORIZ; j++){
            printf("+---");
        }
        printf("+\n");

        //print the middle line with the stones
        for(int j = 0; j < BOARD_SIZE_HORIZ; j++){

            printf("| ");


            int ji = board[j][i];
            if(ji == 1){printf("X");}
            else if(ji == 2){printf("O");}
            else if(ji == 0){printf(" ");}
            else{ printf("%d", ji);}

            printf(" ");

        }
        printf("|\n");

    }

    //print the the last line that makes up the board
    for( int j= 0; j<BOARD_SIZE_HORIZ; j++){
            printf("+---");
    }
    printf("+\n");

    // print the column values
    for( int j= 0; j<BOARD_SIZE_HORIZ; j++){
            printf("  ");
            printf("%d", j+1);
            printf(" ");
    }
    printf(" \n\n");

}

/******************************************************************************
*                                                                             *
*                      Function random_move()                                 *
*                                                                             *
******************************************************************************/
int random_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    //choose a random val
    int i;
    do{
        i = rand()%(BOARD_SIZE_HORIZ) +1;
    //keep choosing until one works
    }while(is_column_full(board, i) == true);

    //update the board wit the chosen value that works
    update_board(board, i, computer_num);

    return i;
}

/******************************************************************************
*                                                                             *
*                      Function player_move()                                 *
*                                                                             *
******************************************************************************/
int player_move(int board[][BOARD_SIZE_VERT], int player_num)

{
    int valid = 0;
    int move = 0;
    // loop until the user gives a valid input
    while(valid == 0){
        // prompt user for input
        printf("Please enter your move: ");
        //get the first int
        scanf("%d", &move);
        //if there is still anything left in the buffer after the int, have the use try again by "deleting" the int
        char c;
        do{
            c = getchar();
            if(c != '\n'){move = 0;}
        }while(c != '\n');
        // check for full columns
        if(move>0 && move<=BOARD_SIZE_HORIZ){
            if(is_column_full(board, move) == true){
                printf("This column is full. Try again!\n");
            }
            // if it is not full, continue
            else{
                valid = 1;
            }
        }
        // if the move is not valid
        else{
            printf("Not a valid move. Enter a column number!\n");
        }

    } /* while valid = 0*/

    //once the move is valid, update with that move
    update_board(board, move, player_num);

    return move;

}

/******************************************************************************
*                                                                             *
*                      Function check_win_or_tie()                            *
*                                                                             *
******************************************************************************/
bool check_win_or_tie(int board[][BOARD_SIZE_VERT], int last_move)
{

    //get state of last stone placed
    int winningStone  =  check_winner(board, last_move);

    //if stone == 1, X wins
    if(winningStone == 1){
        printf("*****************************\n");
		printf("* Player X won!!! Game over *\n");
		printf("*****************************\n");
		return true;
    }

    //if stone == 2, O wins
    if(winningStone == 2){
        printf("*****************************\n");
		printf("* Player O won!!! Game over *\n");
		printf("*****************************\n");;
		return true;
    }

    //if there is no room, tie
    int room = 0;
    for( int i = 0; i< BOARD_SIZE_HORIZ; i++){
        if(is_column_full(board,i+1) == 0 ){
            room = 1;
            break;
        }
    }
    if(room == 0){
        printf("*****************************\n");
		printf("* Game is a tie!! No winner *\n");
		printf("*****************************\n");
		return true;
    }

    //if there is room, but the last stone has less than 4 in a row, continue with game
    if(winningStone == 0){
        return false;
    }

}

int check_win_or_tie1(int board[][BOARD_SIZE_VERT], int last_move)
{

    //get state of last stone placed
    int winningStone  =  check_winner(board, last_move);

    //if stone == 1, X wins
    if(winningStone == 1){
        printf("*****************************\n");
		printf("* Player X won!!! Game over *\n");
		printf("*****************************\n");
		return 1;
    }

    //if stone == 2, O wins
    if(winningStone == 2){
        printf("*****************************\n");
		printf("* Player O won!!! Game over *\n");
		printf("*****************************\n");;
		return 2;
    }

    //if there is no room, tie
    int room = 0;
    for( int i = 0; i< BOARD_SIZE_HORIZ; i++){
        if(is_column_full(board,i+1) == 0 ){
            room = 1;
            break;
        }
    }
    if(room == 0){
        printf("*****************************\n");
		printf("* Game is a tie!! No winner *\n");
		printf("*****************************\n");
		return 0;
    }

    //if there is room, but the last stone has less than 4 in a row, continue with game
    if(winningStone == 0){
        return -12;
    }

}

/******************************************************************************
*                                                                             *
*                     Function is_column_full()                               *
*                                                                             *
******************************************************************************/
bool is_column_full(int board[][BOARD_SIZE_VERT], int m)
{
    // if the top row of the given column is not 0
    if(board[m-1][0] == 0){
        //the column is not full
        return false;
    }
    //if it is not 0, the column is full
    return true;

}

/******************************************************************************
*                                                                             *
*                      Function update_board()                                *
*                                                                             *
******************************************************************************/
void update_board(int board[][BOARD_SIZE_VERT], int m, int player_num)
{
    // for all of the elements in the column starting at the bottom of what the user sees
    for( int i = BOARD_SIZE_VERT-1; i> 0-1; i-- ){
        // if the row of the given column is empty
        if(board[m-1][i] == 0){
            // fill the element with the stone of the given player
            board[m-1][i] = player_num;
            //stop looking for empty spaces. This is important otherwise the entire row will be filled
            break;
        }
    }

}

/******************************************************************************
*                                                                             *
*                      Function check_winner()                                *
*                                                                             *
******************************************************************************/
int check_winner(int board[][BOARD_SIZE_VERT], int last_move)
{

// checking for vertical winner
    int playerStone;
    int vertHigh;
    int vertLow;
    for(int i = 0; i< BOARD_SIZE_VERT; i++){
        //get the first non zero in the column of the last move
        if(board[last_move-1][i] != 0){
            playerStone = board[last_move-1][i]; //set player Stone to the first non zero number
            vertHigh = i; // this is high in terms of the board the user sees, would be low in terms of index
            vertLow = i + 3; // low based on board user sees, sets index "down" 3 stones
            break;
        }
    }
    //check there are at least 4 in a row by making sure that the index of a location 3 beneath the "top" stone is not out of bounds
    if(vertLow < BOARD_SIZE_VERT){
        int vertWin = 1; // default is a win
        // for each element between the bottom stone ant the top, check for opposing stones
        for(int i = vertLow; i > vertLow-4; i-- ){
            // if the stone is not the players
            if(board[last_move-1][i] != playerStone ){
                // set the win status to zero
                vertWin = 0;
                // stop checking stones
                break;
            }
        }
        // if the win status stayed win through all of the stones (they all belong to the player)
        if(vertWin == 1){
            // return a win for the player
            return playerStone;
        }

    }


//////check for horizontal win /////////////////////
    int inARow = 0; // number of stones in a row
    //for all of the stones in the row of the new stone (this is found when checking for vertical win)
    for(int i = 0; i< BOARD_SIZE_HORIZ; i++){
        int stone = board[i][vertHigh];
        //if the stone belongs to the player
        if(stone == playerStone){   // don't forget == not = when checking if
            //update the number in a row
            inARow = inARow+1;
        }
        // if the stone does not belong to the player set the number in a row to zero
        else{inARow = 0;}

//        printf("%d ", inARow);
        // if the number in a row is ever 4, return a win for horizontal
        if(inARow == 4){return playerStone;}
    }
//    printf("\n");

//////////////check win Diagonal Down and Right by user board perspective/////////////////////////
    int upDownStart = vertHigh - (last_move-1); // this might be out of bounds, but the diagonal will capture the last move
    int left_right = 0;
    inARow = 0;
    //for all of the elements in the diagonal of the last stone
    for(int i = upDownStart; i< BOARD_SIZE_VERT; i++){
        // if the indexes are in bounds of the board (because we are going to check ones that are not
        if(i >=0 && left_right< BOARD_SIZE_HORIZ){
//            printf("%d,%d ", left_right, i);
//            printf("%d", board[left_right][i]);
            // if the stone in the given index belongs to the player
            if( board[left_right][i] == playerStone){
                // increment the number in a row
                inARow = inARow+1;
                // if the number in a row is ever 4, return a win for that player
                if(inARow == 4){return playerStone;}
            }
            // if the stone is not the players
            else{
                //reset the number in a row
                inARow = 0;
            }
//            printf("%d", inARow);
        }
        // as the rows go from top to bottom, the columns go form left to right
        left_right = left_right+1;
    }

/////////////check win Diagonal Down and Left by user board perspective/////////////////////////////
    upDownStart = vertHigh - (BOARD_SIZE_HORIZ-(last_move)); // this might be out of bounds, but the diagonal will capture the last move
    left_right = BOARD_SIZE_HORIZ-1;
    inARow = 0;
    for(int i = upDownStart; i< BOARD_SIZE_VERT; i++){
//        printf("%d,%d ", left_right, i);
        if(i >=0 && left_right< BOARD_SIZE_HORIZ){ // see if the indexes are in bounds
//            printf("%d", board[left_right][i]);
            if( board[left_right][i] == playerStone){
                inARow = inARow+1;
                if(inARow == 4){return playerStone;}
            }
            else{
                inARow = 0;
            }
//            printf("%d", inARow);
        }
        // as the rows go from top to bottom, the columns go form right to left
        left_right = left_right-1;
    }


    return 0;

}

/******************************************************************************
*                                                                             *
*                       Function best_move()                                  *
*                                                                             *
*******************************************************************************
*                                                                             *
*  This is the EXTRA-CREDIT function to be used for the student competition.  *
*                                                                             *
******************************************************************************/
int best_move(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int player_number;
    if(computer_num == 2){
        player_number = 1;
    }
    if(computer_num == 1){
        player_number = 2;
    }



    int i = 1;
    while(i< BOARD_SIZE_HORIZ){
        if(is_column_full(board, i) == false){
            update_board(board, i, computer_num);
            //if this move makes either team win, keep it
            if(check_win_or_tie(board, i)){
                return i;
            }
            //otherwise try again
            undo_move(board, i);
    //        display_board(board);
        }
    i++;
    }
    i = 1;
    while(i< BOARD_SIZE_HORIZ){
        if(is_column_full(board, i) == false){
            update_board(board, i, player_number);
            //if this move makes either team win, keep it
            if(check_win_or_tie(board, i)){
                undo_move(board, i);
                update_board(board, i, computer_num);
                return i;
            }
            //otherwise try again
            undo_move(board, i);
    //        display_board(board);
        }
    i++;
    }


    int guess = 4;
    for(int i = 0; i< 7;i++){
        printf("%d, %d", guess, i);
        if(is_column_full(board,guess) == false){
            update_board(board, guess, computer_num);
            return guess;
        }
        i = -1*i;
        guess = guess +i;
    }

}


int best_move2(int board[][BOARD_SIZE_VERT], int computer_num)
{
    int player_number;
    if(computer_num == 2){
        player_number = 1;
    }
    if(computer_num == 1){
        player_number = 2;
    }



    int i = 1;
    while(i< BOARD_SIZE_HORIZ){
        if(is_column_full(board, i) == false){
            update_board(board, i, computer_num);
            //if this move makes either team win, keep it
            if(check_win_or_tie(board, i)){
                return i;
            }
            //otherwise try again
            undo_move(board, i);
    //        display_board(board);
        }
    i++;
    }
    i = 1;
    while(i< BOARD_SIZE_HORIZ){
        if(is_column_full(board, i) == false){
            update_board(board, i, player_number);
            //if this move makes either team win, keep it
            if(check_win_or_tie(board, i)){
                undo_move(board, i);
                update_board(board, i, computer_num);
                return i;
            }
            //otherwise try again
            undo_move(board, i);
    //        display_board(board);
        }
    i++;
    }



    update_board(board, i, computer_num);
    return i;
}


/*=============================================================================
  Function definitions of other functions
=============================================================================*/


void undo_move(int board[][BOARD_SIZE_VERT], int m)
{
    // for all of the elements in the column starting at the bottom of what the user sees
    for( int i = BOARD_SIZE_VERT-1; i> 0-1; i-- ){
        // if the row of the given column is empty
        if(board[m-1][i] == 0){
            // eliminate the previous stone
            board[m-1][i+1] = 0;
            //stop looking for empty spaces. This is important otherwise the entire row will be filled
            break;
        }
    }

}
// If you would like to use functions other than those declared in
// connect4_functions.h and implemented above, put the definitions
// of these functions here.







/******************************************************************************
                                End of file
******************************************************************************/
