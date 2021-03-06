#include<stdio.h>
#include<string.h>

// initializeBoard() - begin
void initializeBoard(char board[][26], int n)
{
	int ii, jj;
	
	// set all the cells to 'U'(unused)	
	for (ii = 0; ii < n; ++ii)
		for (jj = 0; jj < n; ++jj)
			board[ii][jj] = 'U';
			
	// update the middle row/columns with the starting configuration	
	board[n/2-1][n/2-1]	= 'W';
	board[n/2-1][n/2]	= 'B';
	board[n/2][n/2-1]	= 'B';
	board[n/2][n/2]	    = 'W';
}
// initializeBoard() - end

// printBoard() definition - begin
void printBoard(char board[][26], int n)
{
	int ii, jj;
	
	// accomodate the space for the row heading
	printf("  ");
	
	// display the column headings
	for (ii = 0; ii < n; ++ii)
		printf("%c", 'a'+ii);	
	
	printf("\n");
	
	// keep displaying the elements of the board
	for (ii = 0; ii < n; ++ii)
	{
		// display the row heading
		printf("%c ", 'a'+ii);
		
		// display the status of the current cell
		for (jj = 0; jj < n; ++jj)
			printf("%c", board[ii][jj]);
		
		printf("\n");
	}
}
// printBoard() definition - end

bool isMoveInputValid(const char move[], int n)
{
	if (strlen(move) != 2)
	{
		//printf("Move must have two characters only.");
		return false;
	}
	
	if (move[0] < 'a' || move[0] > ('a' + n))
	{
		//printf("First character of the Move must be a lower case alphabet(a-z).");
		return false;
	}
	
	if (move[1] < 'a' || move[1] > ('a' + n))
	{
		//printf("First character of the Move must be a lower case alphabet(a-z).");
		return false;
	}
	
	return true;
}

// positionInBounds() definition - begin
bool positionInBounds(int n, int row, int col)
{
	if (row < 0 || row >= n) return false; // row is either -ve or exceeding the limit
	if (col < 0 || col >= n) return false; // col is either -ve or exceeding the limit
	
	// both row and col are within the limits
	return true;
}
// positionInBounds() definition - end

// checkLegalInDirection() definition - begin
bool checkLegalInDirection(char board[][26], int n, int row, int col,
						   char colour, int deltaRow, int deltaCol)
{
	int newRow = row + deltaRow; // find the index of row to be checked
	int newCol = col + deltaCol; // find the index of the col to be checked
	char oponentColour;          // colour of the oponet
	
	// safety check
	if (deltaRow == 0 && deltaCol == 0)
		return false;
	
	// if the cell is already occupied, return false;
	if (board[row][col] != 'U')
		return false;
	
	// identify the colour of the oponent
	if (colour == 'B') 
		oponentColour = 'W';
	else
		oponentColour = 'B';
	
	// to check if atleast one move can be made on the board	
	bool moveOn = false;
	
	// keep tracking the straight line as far as posssible
	while (positionInBounds(n, newRow, newCol) == true)
	{
		// you reached the end, since you found the oponent on the cell
		if (board[newRow][newCol] != oponentColour)
			break;
		
		// update the row and col to keep moveing in the straight line	
		newRow = newRow + deltaRow;
		newCol = newCol + deltaCol;
		
		// you could make atleast one move
		moveOn = true;
	}
    
    // if you couldn't move, move is illegal
	if (moveOn == false)
		return false;
    
    // if you find the oponent at the end of the straight line, move is legal
    if (board[newRow][newCol] == colour)
		return true;
	
	// by now, move is illegal
	return false;
}
// checkLegalInDirection() definition - end

// updateLegalInDirection() definition - begin
void updateLegalInDirection(char board[][26], int n, int row, int col,
						   char colour, int deltaRow, int deltaCol)
{
	int newRow = row + deltaRow; // find the index of row to be checked
	int newCol = col + deltaCol; // find the index of the col to be checked
	char oponentColour;          // colour of the oponet
	
	// safety check
	if (deltaRow == 0 && deltaCol == 0) return;
	
	// if the cell is already occupied, return false;
	if (board[row][col] != 'U' && board[row][col] != 'X') return;
	
	// identify the colour of the oponent
	if (colour == 'B') 
		oponentColour = 'W';
	else
		oponentColour = 'B';
		
	// to check if atleast one move can be made on the board	
	bool moveOn = false;
	
	// keep tracking the straight line as far as posssible
	while (positionInBounds(n, newRow, newCol) == true)
	{
		// you reached the end, since you found the oponent on the cell
		if (board[newRow][newCol] != oponentColour)
			break;
		
		// update the row and col to keep moveing in the straight line	
		newRow = newRow + deltaRow;
		newCol = newCol + deltaCol;
		
		// you could make atleast one move
		moveOn = true;
	}
    
    // if you couldn't move, move is illegal
	if (moveOn == false)
		return;
    
    // if you don't have the oponent at the end of the straight line, return
    if (board[newRow][newCol] != colour)
    	return;
    
	// go ahead and make the move by inverting the oponet's coins	
    
	// update the row and col to keep moveing in the straight line
	newRow = row + deltaRow;
	newCol = col + deltaCol;
	
	// keep tracking the straight line as far as posssible
	while (positionInBounds(n, newRow, newCol) == true)
	{
		// you reached the end, since you found the oponent on the cell
		if (board[newRow][newCol] != oponentColour)
			break;
			
		// update the cell to X as an indicator	
		board[newRow][newCol] = 'X';
		
		// update the new indices on the straight line
		newRow = newRow + deltaRow;
		newCol = newCol + deltaCol;
	} // end of while
}
// updateLegalInDirection() definition - end

// updateBoard() definition - begin
void updateBoard(char board[][26], int n, char colour, int row, int col)
{
	// check all the 8 directions and invert
	// the coins of the oponent whehever possible
	updateLegalInDirection(board, n, row, col, colour, -1, 0);
	updateLegalInDirection(board, n, row, col, colour, -1, 1);
	updateLegalInDirection(board, n, row, col, colour, 0, 1);
	updateLegalInDirection(board, n, row, col, colour, 1, 1);
	updateLegalInDirection(board, n, row, col, colour, 1, 0);
	updateLegalInDirection(board, n, row, col, colour, 1, -1);
	updateLegalInDirection(board, n, row, col, colour, 0, -1);
	updateLegalInDirection(board, n, row, col, colour, -1, -1);
	
	// mark the current cell with the player colour
	board[row][col] = colour;
	
	// keep updating all the marked cells with colour of the player
	for (int ii = 0; ii < n; ++ii)
	{
		for (int jj = 0; jj < n; ++jj)
		{
			if (board[ii][jj] == 'X')
				board[ii][jj] = colour;
		}
	}
}
// updateBoard() definition - end

// validateFeasibility() definition - begin
bool validateFeasibility(char board[][26], int n, int row, int col, char colour)
{
	bool returnValue = false;
	    
	// check all the 8 directions and capture the outcome as a return value
	// logical OR is performed as the valid direction may happen anytime during
	// checking for legalmove. Otherwise we return the result of last check only
	returnValue = checkLegalInDirection(board, n, row, col, colour, -1, 0);
	returnValue = checkLegalInDirection(board, n, row, col, colour, -1, 1) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, 0, 1) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, 1, 1) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, 1, 0) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, 1, -1) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, 0, -1) || returnValue;
	returnValue = checkLegalInDirection(board, n, row, col, colour, -1, -1) || returnValue;
	
	// return the final result
	return returnValue;
}
// validateFeasibility() definition - end

// displayAvailableMoves() definition - begin
void displayAvailableMoves(char board[][26], int n, char colour)
{
	for (int ii = 0; ii < n; ++ii)
	{
		for (int jj = 0; jj < n; ++jj)
		{
			// display the available moves for both of the colours
			if (validateFeasibility(board, n, ii, jj, colour) == true)
				printf("%c%c\n", 'a'+ii, 'a'+jj);
		}
	}
}
// displayAvailableMoves() definition - end

// main() definition - begin
int main()
{
	// variable definitions
	char board[26][26];			// the 2D board
	char move[3];				// the move
	char cComputerPlayColour;	// represents the computer playing colour
	char cHumanPlayColour;		// represents the human playing colour
	char cCurrentPlayer;		// represents the current player
	int  ii, jj, n;
	
	// read the dimensions of the board
	printf("Enter the board dimension: ");
	scanf("%d", &n);
	
	// this is a safety check to avoid invalid input
	// if the dimensions are invalid, quit the program
	if (n <= 1 || n > 26 || n%2 == 1)
	{
		printf("Invalid input, n must be an even number between 2 and 26.");
		return 1;
	}
	
	printf("Computer plays (B/W): ");
	fflush(stdin);
	scanf("%c", &cComputerPlayColour);
	if (cComputerPlayColour != 'B' && cComputerPlayColour != 'W')
	{
		printf("Invalid colour.");
		return 1;
	}
	
	// set the play color of the human
	if (cComputerPlayColour == 'B')
	{
		cHumanPlayColour = 'W';
		// set the first colour to black
		cCurrentPlayer = 'C';
	}
	else
	{
		cHumanPlayColour = 'B';
		// set the first colour to black
		cCurrentPlayer = 'H';
	}
	
	// setup the board
	initializeBoard(board, n);
	
	// display the current state of the board
	printBoard(board, n);
	
	do
	{
		if (cCurrentPlayer == 'H')
		{
			// read the move of the human
			printf("Enter move for colour %c (RowCol): ", cHumanPlayColour);
			// read the move
			scanf("%s", move);
		
			// check if the entered move is proper
			/*
			if (isMoveInputValid(move, n) == false)
		   	{
		   		printf("Invalid move.\n");
		   		printf("%c player wins.", cComputerPlayColour);
				return 1;
			}*/
		 
			// check if the indices are within valid range	
			bool bPositionValid = positionInBounds(n, move[0]-'a', move[1]-'a');
			// quit the program if the indexes are out of bound
			if (bPositionValid == false)
			{
				printf("Invalid move.\n");
		   		printf("%c player wins.", cComputerPlayColour);
			}
			
			// update board with human move
			updateBoard(board, n, cHumanPlayColour, move[0]-'a', move[1]-'a');
			printBoard(board, n);
			
			// update the player for the next round
			cCurrentPlayer = 'C';
		}
		else
		{
			printf("Computer places %c at %s.\n", cComputerPlayColour, "aa");
			updateBoard(board, n, cComputerPlayColour, 0, 0);//move[0]-'a', move[1]-'a');
			printBoard(board, n);
			// update the player for the next round
			cCurrentPlayer = 'H';
		}
		
	} while(1);
	
	/*
	// display the current state of the board
	printBoard(board, n);
	
	// turn1: white, turn2: black
	for (int turn = 1; turn <= 2; ++turn)
	{
		printf("Available moves for ");
		
		// decide the colour of the player
		if (turn == 1)
			colour = 'W';
		else
			colour = 'B';
		printf("%c\n", colour);
		
		// display the available moves for the current player
		displayAvailableMoves(board, n, colour);
	}
	
	// read the move
	printf("Enter a move:\n");
	scanf("%s", configuration);
	
	// check if the move is valid 
	if (validateFeasibility(board, n, configuration[1]-'a', configuration[2]-'a', configuration[0]) == true)
	{
		printf("Valid move.\n");
		
		// update the board with the impact of the current move
		updateBoard(board, n, configuration[0], configuration[1]-'a', configuration[2]-'a');
	}
	else // indicates invalid move	
	{
		printf("Invalid move.\n");
	}
	
	// display the current state of the board
	printBoard(board, n);
	
	// we are done!!!
	return 0;
	*/
}
// main() definition - end
