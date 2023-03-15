#define _CRT_SECURE_NO_WARNINGS

/***************************************************
 * Hackathon - Summer 2021                         *
 *                                                 *
 * This program implements the Reversi board game  *
 *                                                 *
 ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /*************/
 /* Constants */
 /*************/

#define GRID_SIZE 8  /* The size of each edge of the board */

#define SEED 1  /* Used by randomPlayer */

#define FIRST  1 /* Player 1   */
#define SECOND 2 /* Player 2   */
#define EMPTY  0 /* Empty slot */

#define TRUE	1
#define FALSE	0

 /* End of constants */

 /*************************/
 /* Function declarations */
 /*************************/

 /* Tasks functions */
void createBoard(int[][GRID_SIZE]);					/* Task 1 */
int isLegal(int[][GRID_SIZE], int, int, int);	/* Task 2 */
int play(int[][GRID_SIZE], int, int, int);	/* Task 3 */
int benefit(int[][GRID_SIZE], int, int, int);	/* Task 4 */
int possibleMoves(int[][GRID_SIZE], int[][2], int);	/* Task 5 */
int hasMoves(int[][GRID_SIZE], int);				/* Task 6 */
int findTheWinner(int[][GRID_SIZE]);					/* Task 7 */
int gameOver(int[][GRID_SIZE]);					/* Task 8 */

/* Additional functions */
void interactivePlay();
void randomPlayer(int[][GRID_SIZE], int);
void displayBoard(int[][GRID_SIZE]);


 /* End of function declarations */


 /* ---------------------------------------------------------------------------------------- *
  * The main function																		*
  * ---------------------------------------------------------------------------------------- */
int main()
{
	interactivePlay();

	getchar();
	return 0;
}



/* ---------------------------------------------------------------------------------------- *
 * Task 1 - Creates a new board with 2 pieces for each player in their starting position	*
 * ---------------------------------------------------------------------------------------- */
void createBoard(int board[][GRID_SIZE])
{
	int i, j;
	for (i = 0; i < GRID_SIZE; i++) 
	{
		for (j = 0; j < GRID_SIZE; j++)
			board[i][j] = 0;
	}

	board[(GRID_SIZE / 2) - 1][(GRID_SIZE / 2) - 1] = 1;
	board[(GRID_SIZE / 2) - 1][GRID_SIZE / 2] = 2;
	board[GRID_SIZE / 2][(GRID_SIZE / 2) - 1] = 2;
	board[GRID_SIZE / 2][GRID_SIZE / 2] = 1;
}




/* ----------------------------------------------------------------------------------------- *
 * Task 2 - returns 1 (TRUE) if <player> can legally put its piece at (<row>,<column>) on    *
 * <board>, or 0 (FALSE) otherwise                                                           *
 * ----------------------------------------------------------------------------------------- */
int isLegal(int board[][GRID_SIZE], int player, int row, int column)
{
	int boolean_result = 0, i = row + 1, j = column - 1;
	//direction bottom left
	while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE && j > 0)
	{
		i++;
		j--;
	}
	if (board[i][j] == player && (i != row + 1 || j != column - 1))
		boolean_result = 1;
	//bottom
	i = row + 1;
	j = column;
	while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1)
	{
		i++;
	}
	if (board[i][j] == player && (i != row + 1 || j != column))
		boolean_result = 1;

	//bottom right
	i = row + 1;
	j = column + 1;
	while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
	{
		i++;
		j++;
	}
	if (board[i][j] == player && (i != row + 1 || j != column + 1))
		boolean_result = 1;
	//right
	i = row;
	j = column + 1;
	while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
	{
		j++;
	}
	if (board[i][j] == player && (i != row || j != column + 1))
		boolean_result = 1;
	//top right
	i = row - 1;
	j = column + 1;
	while (player != board[i][j] && board[i][j] != 0 && i > 0 && j < GRID_SIZE - 1)
	{
		i--;
		j++;
	}
	if (board[i][j] == player && (i != row - 1 || j != column + 1))
		boolean_result = 1;
	//top
	i = row - 1;
	j = column;
	while (player != board[i][j] && board[i][j] != 0 && i > 0)
	{
		i--;
	}
	if (board[i][j] == player && (i != row - 1 || j != column))
		boolean_result = 1;
	//top left
	i = row - 1;
	j = column - 1;
	while (player != board[i][j] && board[i][j] != 0 && i > 0 && j > 0)
	{
		i--;
		j--;
	}
	if (board[i][j] == player && (i != row - 1 || j != column - 1))
		boolean_result = 1;
	//left
	i = row;
	j = column - 1;
	while (player != board[i][j] && board[i][j] != 0 && j > 0)
	{
		j--;
	}
	if (board[i][j] == player && (i != row || j != column - 1))
		boolean_result = 1;
	if (boolean_result == 1)
		return TRUE;
	else if (boolean_result == 0)
		return FALSE;
}




/* ---------------------------------------------------------------------------------- *
 * Task 3 - Changes the board after <player> plays the move (<row>,<column>)		  *
 * ---------------------------------------------------------------------------------- */
int play(int board[][GRID_SIZE], int player, int row, int column)
{
	int i = row + 1, j = column - 1, steps = 0;
	if (isLegal(board, player, row, column))
	{
		board[row][column] = player;

		//direction bottom left
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE && j > 0)
		{
			i++;
			j--;
			steps++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column - 1)))
			steps = 0;
		i = row + 1;
		j = column - 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i++;
			j--;
		}

		//bottom
		i = row + 1;
		j = column;
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1)
		{
			i++;
			steps++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column)))
			steps = 0;
		i = row + 1;
		j = column;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i++;
		}

		//bottom right
		i = row + 1;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
		{
			steps++;
			i++;
			j++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column + 1)))
			steps = 0;
		i = row + 1;
		j = column + 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i++;
			j++;
		}

		//right
		i = row;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
		{
			steps++;
			j++;
		}
		if (!(board[i][j] == player && (i != row || j != column + 1)))
			steps = 0;
		i = row;
		j = column + 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			j++;
		}

		//top right
		i = row - 1;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i > 0 && j < GRID_SIZE - 1)
		{
			steps++;
			i--;
			j++;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column + 1)))
			steps = 0;
		i = row - 1;
		j = column + 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i--;
			j++;
		}

		//top
		i = row - 1;
		j = column;
		while (player != board[i][j] && board[i][j] != 0 && i > 0)
		{
			steps++;
			i--;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column)))
			steps = 0;
		i = row - 1;
		j = column;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i--;
		}

		//top left
		i = row - 1;
		j = column - 1;
		while (player != board[i][j] && board[i][j] != 0 && i > 0 && j > 0)
		{
			steps++;
			i--;
			j--;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column - 1)))
			steps = 0;
		i = row - 1;
		j = column - 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			i--;
			j--;
		}


		//left
		i = row;
		j = column - 1;
		while (player != board[i][j] && board[i][j] != 0 && j > 0)
		{
			steps++;
			j--;
		}
		if (!(board[i][j] == player && (i != row || j != column - 1)))
			steps = 0;
		i = row;
		j = column - 1;
		while (steps > 0)
		{
			board[i][j] = player;
			steps--;
			j--;
		}
		return TRUE;
	}
	return FALSE;
}




/* ------------------------------------------------------------------------------ *
 * Task 4 - Returns the number of opponent pieces that will be captured as a	  *
 * result of the move (<row>,<column>) of <player> on <board>                     *
 * ------------------------------------------------------------------------------ */
int benefit(int board[][GRID_SIZE], int player, int row, int column)
{
	int i = row + 1, j = column - 1, total_steps = 0, steps = 0;
	if (isLegal(board, player, row, column))
	{
		board[row][column] = player;
		//direction bottom left
		while (board[i][j] != player && board[i][j] != 0 && i < GRID_SIZE && j > 0)
		{
			i++;
			j--;
			steps++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column - 1)))
			steps = 0;
		total_steps += steps;
		//bottom
		i = row + 1;
		j = column;
		while (board[i][j] != player && board[i][j] != 0 && i < GRID_SIZE - 1)
		{
			i++;
			steps++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column)))
			steps = 0;
		total_steps += steps;
		//bottom right
		i = row + 1;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
		{
			steps++;
			i++;
			j++;
		}
		if (!(board[i][j] == player && (i != row + 1 || j != column + 1)))
			steps = 0;
		total_steps += steps;
		//right
		i = row;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i < GRID_SIZE - 1 && j < GRID_SIZE - 1)
		{
			steps++;
			j++;
		}
		if (!(board[i][j] == player && (i != row || j != column + 1)))
			steps = 0;
		total_steps += steps;
		//top right
		i = row - 1;
		j = column + 1;
		while (player != board[i][j] && board[i][j] != 0 && i > 0 && j < GRID_SIZE - 1)
		{
			steps++;
			i--;
			j++;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column + 1)))
			steps = 0;
		total_steps += steps;

		//top
		i = row - 1;
		j = column;
		while (player != board[i][j] && board[i][j] != 0 && i > 0)
		{
			steps++;
			i--;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column)))
			steps = 0;
		total_steps += steps;

		//top left
		i = row - 1;
		j = column - 1;
		while (player != board[i][j] && board[i][j] != 0 && i > 0 && j > 0)
		{
			steps++;
			i--;
			j--;
		}
		if (!(board[i][j] == player && (i != row - 1 || j != column - 1)))
			steps = 0;
		total_steps += steps;

		//left
		i = row;
		j = column - 1;
		while (player != board[i][j] && board[i][j] != 0 && j > 0)
		{
			steps++;
			j--;
		}
		if (!(board[i][j] == player && (i != row || j != column - 1)))
			steps = 0;
		total_steps += steps;
		return total_steps;
	}
	return FALSE;
}



/* ------------------------------------------------------------------------------ *
 * Task 5 - Updates an array of all the possible moves of <player> on <board>.    *
 * Returns the number of possible moves (number of the rows that were updated).   *
 * The moves are ordered by the row number, and in each row by the column number  *
 * ------------------------------------------------------------------------------ */
int possibleMoves(int board[][GRID_SIZE], int movesArray[][2], int player)
{
	int i = 0, j = 0, counter = 0;
	for (i = 0; i < GRID_SIZE; i++) {
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (isLegal(board, player, i, j))
			{
				movesArray[counter][0] = i;
				movesArray[counter][1] = j;
				counter++;
			}
		}
	}
	return counter;
}



/* ---------------------------------------------------------------- *
 * Task 6 - Return 1 (TRUE) if <player> has a legal move on <board>	*
 * or 0 (FALSE) elsewhere.											*
 * ---------------------------------------------------------------- */
int hasMoves(int board[][GRID_SIZE], int player)
{
	int i = 0, j = 0, hasmoves = 0;
	for (i = 0; i < GRID_SIZE; i++) {
		for (j = 0; j < GRID_SIZE; j++)
		{
			if (isLegal(board, player, i, j))
			{
				hasmoves++;
			}
		}
	}
	if (hasmoves > 0)
		return TRUE;
	return FALSE;
}



/* -------------------------------------------------------------------------------- *
 * Task 7 - Returns the player number who has more pieces on the <board>,           *
 * or 0 if it is a tie			                                                    *
 * -------------------------------------------------------------------------------- */
int findTheWinner(int board[][GRID_SIZE])
{
	int flag1 = 0, flag2 = 0, i, j;
	for (i = 0; i < GRID_SIZE; i++) 
	{
		for (j = 0; j < GRID_SIZE; j++) 
		{
			if (board[i][j] == 1)
				flag1++;
			else if (board[i][j] == 2)
				flag2++;
		}
	}
	if (flag1 == flag2)
		return 0;
	else if (flag1 < flag2)
		return SECOND;
	else if (flag1 > flag2)
		return FIRST;
}



/* ------------------------------------------------------------------------ *
 * Task 8 - returns 1 (TRUE) if there are no empty cells or there are no    *
 * legal moves for any of the players.								  		*
 * ------------------------------------------------------------------------ */
int gameOver(int board[][GRID_SIZE])
{
	int flag0 = 0, flag1 = 0, flag2 = 0, i, j;
	for (i = 0; i < GRID_SIZE; i++) 
	{
		for (j = 0; j < GRID_SIZE; j++) 
		{
			if (board[i][j] == 1)
				flag1++;
			else if (board[i][j] == 2)
				flag2++;
			else
				flag0++;
		}
	}
	if (flag0 == 0 || flag1 == 0 || flag2 == 0)
		return TRUE;
	return FALSE;
}




/*****************************************************************************************/
/*********************************** Additional functions ********************************/
/*****************************************************************************************/


/* ----------------------------------------------------------- *
 * Play an interactive game between the computer and the user  *
 * ----------------------------------------------------------- */
void interactivePlay()
{
	int board[GRID_SIZE][GRID_SIZE];
	int row, column, winner;
	unsigned int seed = SEED;

	createBoard(board);
	displayBoard(board);

	printf("\nWelcome to the most magnificent Reversi Game!\n");

	/* Seed for the random player */
	srand(seed);

	printf("You are player 1... \n");

	/* Check whether the game is not over */
	while (!gameOver(board))
	{
		/* If player 1 has no moves - skip to player 2 */
		if (hasMoves(board, FIRST))
		{
			printf("\nPlay:\n");
			printf("Enter row and column: ");
			scanf("%d %d", &row, &column);

			while (!(isLegal(board, FIRST, row, column)))
			{
				printf("Not a legal move! Please try again...\n");
				printf("Enter row and column: ");
				scanf("%d %d", &row, &column);
			}

			play(board, FIRST, row, column);
			displayBoard(board);
		}
		else
			printf("You can't play, there are no legal moves. Player 2 will play again\n");

		printf("May I (player 2) play? (press ENTER for Yes)\n");
		getchar();
		getchar();

		/* If player 2 has no moves - skip to player 1 */
		if (hasMoves(board, SECOND))
		{
			randomPlayer(board, SECOND);
			displayBoard(board);
		}
		else
			printf("I can't play, there are no legal moves. Player 1 will play again\n");
	} /* End of while(!gameOver(board....) */

	/* Declare the winner */
	winner = findTheWinner(board);

	if (winner == FIRST)
	{
		printf("\n\t *************************");
		printf("\n\t * You are the winner !! *");
		printf("\n\t *************************\n");
	}
	else if (winner == SECOND)
		printf("\nYou lost :( \n");
	else
		printf("\nThe game ended in a tie...\n");
} /* End of interactivePlay */


/* -------------------------------------------------------------------------------*
 * Updates the board after <player> randomally puts a new piece on <board>.		  *
 * If no move of <player> can be done, the <board> does not change				  *
 * -------------------------------------------------------------------------------*/
void randomPlayer(int board[][GRID_SIZE], int player)
{
	/* Define the parameters and their initial values */
	int movesArray[GRID_SIZE * GRID_SIZE][2];
	int numOfMoves, chosenMove;
	int row, column;

	/* number of possible moves */
	numOfMoves = possibleMoves(board, movesArray, player); /* Gets the possible moves of <player> */

	/* The chosen move out of all the possible moves */
	chosenMove = (int)((double)rand() / ((double)RAND_MAX + 1) * (numOfMoves)); /* The index (in movesArray) of the move */

	printf("Move %d out of %d\n", chosenMove, numOfMoves);

	if (chosenMove != -1)
	{ /* There is a possible move (with benefit > 0) */
		row = movesArray[chosenMove][0];
		column = movesArray[chosenMove][1];
		play(board, player, row, column);
	}
	/* Else - we didn't change the board */
} /* End of randomPlayer */



/* ---------------------------------------------------------------------------------------- *
 * Displays the board																		*
 * ---------------------------------------------------------------------------------------- */
void displayBoard(int board[][GRID_SIZE])
{
	int row, column;

	/* First row */
	printf("   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf(" %d ", column);

	/* Second row */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");

	/* The board */
	for (row = 0; row < GRID_SIZE; row++)
	{
		printf("\n%d |", row);
		for (column = 0; column < GRID_SIZE; column++)
		{
			if (board[row][column] != EMPTY)
				printf(" %d ", board[row][column]);
			else
				printf("   ");
		} /* End of for column */
		printf("|");
	} /* End of for row */

	/* Last row) */
	printf("\n   ");
	for (column = 0; column < GRID_SIZE; column++)
		printf("---");
	printf("\n");
} /* End of displayBoard */