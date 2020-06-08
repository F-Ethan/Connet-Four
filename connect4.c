
/******************************************************************************
*
* File name: connect4.c
*
* Author: ECE15 Instructors
*         ecefifteen@gmail.com
*
*     Lab #: 4
* Problem #: 1
*
******************************************************************************/


/*-----------------------------------------------------------------------------
   Include files
-----------------------------------------------------------------------------*/
#include "connect4_functions.h"


/*=============================================================================
  Constants and definitions: Given in connect4_functions.h
=============================================================================*/


/*=============================================================================
  Global variables: None
=============================================================================*/


/*=============================================================================
  Forward function declarations: Given in connect4_functions.h
=============================================================================*/


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 This program plays a game of Connect-4 between the user (herein called Alice)
 and the computer. The declarations of all the functions used in this program
 are in connect4_functions.h. The definitions of these functions are expected
 in connect4_functions.c.

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/

int main()
{
   int board[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = { {0} };
   int boardReset[BOARD_SIZE_HORIZ][BOARD_SIZE_VERT] = { {0} };
   int player_num, computer_num;
   int last_move;


   /* Ask Alice if she wants to go first */
   player_num = 2;//print_welcome();
   if (player_num == 1) computer_num = 2;
   else computer_num = 1;

   /* If Alice wants to go first, let her make a move */
   if (player_num == 1)
   {
      display_board(board);
      last_move = player_move(board,player_num);
      display_board(board);
   }


   /* The main loop */

   int check;

   int games = 0;
   int score1 = 0;
   int score2 = 0;
   int tie = 0;
while (games < 5){



      /* Make a computer move, then display the board */
      last_move = best_move2(board,computer_num);
//      printf("Computer moved in column: %d\n", last_move);
      display_board(board);

      /* Check whether the computer has won */
      check = check_win_or_tie1(board,last_move);
      printf("check : %d\n",check);
      if (check == 0 | check == 1 | check == 2){
          switch(check){

            case 0:
                tie ++;
                break;

            case 1:
                score1++;
                break;

            case 2:
                score2++;
                break;

           }

          games++;
          printf("game #%d\n", games);
          for(int i = 0; i< BOARD_SIZE_HORIZ; i++){
                for( int j = 0; j< BOARD_SIZE_VERT; j++){
                    board[i][j] = boardReset[i][j];
                }
           }

      }


      /* Let Alice make a move, then display the board */
      last_move = best_move(board,player_num);
      display_board(board);

      /* Check whether Alice has won */
      check = check_win_or_tie1(board,last_move);
      printf("check : %d\n",check);
      if (check == 0 | check == 1 | check == 2){
          switch(check){

            case 0:
                tie ++;
                break;

            case 1:
                score1++;
                break;

            case 2:
                score2++;
                break;

           }

          games++;
          printf("game #%d\n", games);
          for(int i = 0; i< BOARD_SIZE_HORIZ; i++){
                for( int j = 0; j< BOARD_SIZE_VERT; j++){
                    board[i][j] = boardReset[i][j];
                }
           }

      }



   } /* end of while (games<100) */

    printf("score 1: %d\n", score1);
    printf("score 2: %d\n", score2);
    printf("ties: %d\n", tie);

} /* end of main() */



/*=============================================================================
  Function definitions: Expected in connect4_functions.c
=============================================================================*/


/******************************************************************************
                                End of file
******************************************************************************/
