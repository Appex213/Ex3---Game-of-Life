/******************************************
* Matan Ben Moshe
* 208583070
* 83-120-04
* ex2
******************************************/

// Standard library
#include <stdio.h>
// Extra library for exit() function
#include <stdlib.h>

/*------------------------------------------------------Github Commit RC1-------------------------------------------------------------*/

//Constants
#define MAX_HEIGHT 70
#define MAX_WIDTH 70
#define MIN_WIDTH 10
#define MIN_HEIGHT 10
#define CLR_AI 'G'
#define CLR_PLYR 'R'

// Function Decleration.
void GameStart(char board[MAX_HEIGHT][MAX_WIDTH], int* height, int* width, long*maxGen, long* Gen);
void InitializeBoard(char board[MAX_HEIGHT][MAX_WIDTH], int* height, int* width);
void GetDimensions(int* height, int* width);
void LiveCells(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width);
int IsCellPosValid(int i, int j, int height, int width, int color, char board[MAX_HEIGHT][MAX_WIDTH]);
void PrintBoard(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width);
void GamePlay(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen);
void TurnPlayer(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen);
void TurnAI(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen);
void AICellChoice(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width);
void AdvanceGen(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width);
char AdjacentColor(char board[MAX_HEIGHT][MAX_WIDTH], int i, int j, int height, int width);
void GetMaxGen(long* maxGen);
void CheckVictory(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long Gen, int doPrintBoard);



/*************************************************************************
Function name: Main
Input: None
Output: None
The function operation: Calls to game logic function, houses global (as in used throuout the program, not actually global) variables.
************************************************************************/
int main()
{
	char board[MAX_HEIGHT][MAX_WIDTH];
	int height, width;
	long maxGen = -1, Gen = 0;

	GameStart((char (*)[MAX_WIDTH]) board, &height, &width, &maxGen, &Gen);
	GamePlay((char (*)[MAX_HEIGHT]) board, height, width, maxGen, &Gen);


	return 0;
}

/*************************************************************************
Function name: GameStart
Input: The board, user defined borders, max generation (pointers, not yet defined) and current gen.
Output: None
The function operation: Calls to game initialization functions to get the user's borders, # of cells and # of generations to play. 
************************************************************************/

void GameStart(char board[MAX_HEIGHT][MAX_WIDTH], int* height, int* width, long* maxGen, long* Gen)
{
	printf("Welcome to the game of life!\nSettings:\n");
	InitializeBoard((char (*)[MAX_HEIGHT]) board, height, width);
	// Check if board is empty, or only one color was added.
	CheckVictory((char (*)[MAX_HEIGHT]) board, *height, *width, *maxGen, *Gen, -10);
	GetMaxGen(maxGen);
	AdvanceGen((char (*)[MAX_HEIGHT]) board, *height, *width);
	printf("Welcome to the game of life!\nThis is the initial board:\n");
	PrintBoard((char (*)[MAX_HEIGHT]) board, *height, *width);
	// Check if after initial gen board is empty, one color left, or maxGen is 0.
	CheckVictory((char (*)[MAX_HEIGHT]) board, *height, *width, *maxGen, *Gen, -10);

	return;
}

/*************************************************************************
Function name: InitializeBoard
Input: Board , height and width pointers
Output: None
The function operation: Sets entire board to '-', then calls functions to get user borders, initial cells and prints the board.
************************************************************************/

void InitializeBoard(char board[MAX_HEIGHT][MAX_WIDTH], int* height, int* width)
{
	int i, j;
	// Set entire board as '-'
	for (i = 0; i < MAX_HEIGHT; i++)
		for (j = 0;j < MAX_WIDTH;j++)
			board[i][j] = '-';
	GetDimensions(height, width);
	LiveCells((char(*)[MAX_HEIGHT]) board, *height, *width);
	PrintBoard((char(*)[MAX_HEIGHT]) board, *height, *width);
	return;
}


/*************************************************************************
Function name: GetDimensions
Input: Height and width pointers
Output: None
The function operation: Gets board dimensions from user, and checks for invalid input. 
************************************************************************/

void GetDimensions(int* height, int* width)
{
	do
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	// Check to see if user value is within accepted range.
	} while (*width > MAX_WIDTH || *width < MIN_WIDTH);
	do
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	// Check to see if user value is within accepted range.
	} while (*height > MAX_HEIGHT || *height < MIN_HEIGHT);
	return;

}

/*************************************************************************
Function name: LiveCells
Input: Board pointer and borders' value.
Output: None
The function operation: Gets initial cell count and cells position from user, and call to IsCellPosValid to check if position is valid.
************************************************************************/

void LiveCells(char board[MAX_HEIGHT][MAX_WIDTH] ,int height ,int width)
{
	int i, j, n, cellCount, accepted;
	char color;
	// Maximum cells possible withis borders
	int maxCellCount = height*width;
	do
	{
		printf("Enter number of living cells (0-%d):\n", maxCellCount);
		scanf("%d", &cellCount);
	//Input check
	} while (cellCount > maxCellCount || cellCount < 0);
	for ( n = 0; n < cellCount; n++)
	{
		do
		{
			printf("Enter x y and color (R/G):\n");
			scanf("%d %d %c", &i, &j, &color);
			if (color == 'g')
					color = 'G';
			if (color == 'r')
					color = 'R';
			// Check to see if position is already occupied, outside borders or chosen color is invalid.
			accepted = IsCellPosValid(i, j, height, width, color ,(char (*)[MAX_HEIGHT]) board);
		} while (accepted != 1);
		board[i][j] = color;
	}
	printf("\n");
	return;
}

/*************************************************************************
Function name:IsCellPosValid
Input:Cell position, color, board and size
Output: 1 if position is valid, 0 otherwise.
The function operation: Check to see if position is already occupied, outside borders or chosen color is invalid.
************************************************************************/

int IsCellPosValid(int i, int j, int height, int width, int color, char board[MAX_HEIGHT][MAX_WIDTH])
{
	int valid = 0;
	if (i < height && i >= 0 && j < width && j >= 0)
		if (color == 'R' || color == 'G')
			if (board[i][j] == '-')
				valid = 1;
	return valid;
}

/*********************************************************************************************
Function name: PrintBoard
Input: Board and size
Output: None
The function operation: Prints the board.
**********************************************************************************************/

void PrintBoard(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width)
{
	int i, j;

	for (i = 0; i < height; i++)
	{
		for (j = 0;j < width;j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
	printf("\n");
	return;
}

/*********************************************************************************************
Function name: GetMaxGen
Input: maxGen pointer
Output: None
The function operation: Gets maximum # of generations to play
**********************************************************************************************/

void GetMaxGen(long* maxGen)
{
	printf("Enter number of generations(>=0):\n");
	scanf("%d", maxGen);
	printf("\n");

}

/*********************************************************************************************
Function name: GamePlay
Input: Board and size, max generation and current generation.
Output: None
The function operation: Handles player and AI turns and call to logic functions accordingly.
**********************************************************************************************/

void GamePlay(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen)
{
	int i;
	for (i = 0; i < maxGen; i++)
	{
		if (i % 2 == 0)
		{
			printf("R is playing\n");
			TurnPlayer((char (*)[MAX_HEIGHT]) board, height, width, maxGen, Gen);
		}
		else
		{
			printf("G is playing\n");
			TurnAI((char (*)[MAX_HEIGHT]) board, height, width, maxGen, Gen);
		}
	}
	return;
}

/*********************************************************************************************
Function name:TurnPlayer	
Input: Board and size, max gen and current gen
Output: None
The function operation: Player turn functions. Gets cell position from player, checks for victory, calculates next gen board, prints the board and checks for victory again.
**********************************************************************************************/

void TurnPlayer(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen)
{
	//doPrintBoard - if victory conditions are met before processing the board, print the board before victory message.
	int i, j, doPrintBoard = *Gen;
	printf("x y:\n");
	scanf("%d %d", &i, &j);
	board[i][j] = 'R';
	//Check if victory conditions are met before processing the board.
	CheckVictory((char(*)[MAX_HEIGHT]) board, height, width, maxGen, *Gen, doPrintBoard);
	*Gen += 1;
	AdvanceGen((char (*)[MAX_HEIGHT]) board, height, width);
	PrintBoard((char (*)[MAX_HEIGHT]) board, height, width);
	//Check if victory conditions are met after processing the board.
	CheckVictory((char(*)[MAX_HEIGHT]) board, height, width, maxGen, *Gen, doPrintBoard);

	return;
}

/*********************************************************************************************
Function name:TurnAI
Input: Board and size, max gen and current gen
Output: None
The function operation: AI turn functions. Gets cell position from AI algorithem, checks for victory, calculates next gen board, prints the board and checks for victory again.
**********************************************************************************************/

void TurnAI(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long* Gen)
{
	// Same as in TurnPlayer
	int doPrintBoard = *Gen;
	// Choose cell according to AI algorithem.
	AICellChoice((char (*)[MAX_HEIGHT]) board, height, width);
	printf("\n");
	//Check if victory conditions are met before processing the board.
	CheckVictory((char(*)[MAX_HEIGHT]) board, height, width, maxGen, *Gen, doPrintBoard);
	AdvanceGen((char (*)[MAX_HEIGHT]) board, height, width);
	*Gen += 1;
	PrintBoard((char (*)[MAX_HEIGHT]) board, height, width);
	//Check if victory conditions are met after processing the board.
	CheckVictory((char(*)[MAX_HEIGHT]) board, height, width, maxGen, *Gen, doPrintBoard);

	return;
}

/*********************************************************************************************
Function name:AICellChoice
Input: Board and size
Output: None
The function operation: Chooses cell for the AI according to algorithem:
									1. First enemy cell with 2 or 3 nighboors.
									2. Otherwise, first dead cell with 2 or 3 nighboors and at least 2 enemy nighboors.
									3. Otherwise, first enemy cell.
**********************************************************************************************/

void AICellChoice(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width)
{
	int i, j, a;
	//Scans board for 1st condition, and returns if met.
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
		{
			//Gets # of nighboors
			a = AdjacentTo((char (*)[MAX_HEIGHT]) board, i, j, height, width);
			if (board[i][j] == 'R' && a > 1 && a < 4)
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}
	//Scans board for 2nd condition, and returns if met.
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
		{
			//Gets # of nighboors
			a = AdjacentTo((char (*)[MAX_HEIGHT]) board, i, j, height, width);
			if (board[i][j] == '-' && AdjacentColor((char (*)[MAX_HEIGHT]) board, i, j, height, width) == 'R' && a > 1 && a < 4)
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}
	//Scans board for 3rd condition, and returns.
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
		{
			//Gets # of nighboors
			a = AdjacentTo((char (*)[MAX_HEIGHT]) board, i, j, height, width);
			if (board[i][j] == 'R')
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}

}

/*********************************************************************************************
Function name: AdvanceGen
Input: Board and size
Output: None
The function operation: Function to calculate next gen board according to game rules:
														1. Cell with 1 or less nighboors will die.
														2. Cell with 4 or more nighboors will die.
														3. Dead cell with 3 nighboors will be revived to the color most common out of its nighboors.
														4. Cell (alive) with 2 or 3 nighboors will stay as is.
**********************************************************************************************/

void AdvanceGen(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width)
{
	int i, j, a;
	// Temp board, so that one change will not affect other cells.
	char newBoard[MAX_HEIGHT][MAX_WIDTH];
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
	{
		// Get # of nighboors
		a = AdjacentTo((char (*)[MAX_HEIGHT]) board, i, j, height, width);
		// Condition 4.
		if (a == 2)
			newBoard[i][j] = board[i][j];
		if (a == 3)
			//Condition 3.
			if (board[i][j]=='-')
				newBoard[i][j] = AdjacentColor((char (*)[MAX_HEIGHT]) board, i, j, height, width);
			//Condition 4.
			else
				newBoard[i][j] = board[i][j];
		//Conditions 1 and 2.
		if (a < 2 || a > 3)
			newBoard[i][j] = '-';


	}
	//Copy changes from temp board to original board
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
			board[i][j] = newBoard[i][j];


	return;
}

/*********************************************************************************************
Function name: AdjacentTo
Input: Board, size and cell position.
Output: # of nighboors.
The function operation: Scans the 8 cells surrounding the chosen cell and counts the nighboors.
**********************************************************************************************/

int AdjacentTo(char board[MAX_HEIGHT][MAX_WIDTH], int i, int j, int height, int width)
{
	int k, l, count = 0;
	//Scan around the cell.
	for (k = -1; k <= 1; k++)
	{
		for (l = -1; l <= 1; l++)
		{
			// Do not count the cell itself.
			if (k || l)
				// See XAdd and Yadd descriptions.
				if (board[XAdd(i, k, height)][YAdd(j, l, width)] != '-')
					count++;
		}
	}
	return count;
}

/*********************************************************************************************
Function name:XAdd
Input: Cell X (height) index in the board, height index around the cell and board height
Output: Correct X index.
The function operation: Wraps around the X index, if cell is on a borders gets nighboors from other side.
**********************************************************************************************/

int XAdd(int i, int a, int height)
{
	i += a;
	if (i < 0) 
		i += height;
	if (i >= height) 
		i -= height;
	return i;
}

/*********************************************************************************************
Function name:YAdd
Input: Cell Y (width) index in the board, width index around the cell and board height
Output: Correct Y index.
The function operation: Wraps around the Y index, if cell is on a borders gets nighboors from other side.
**********************************************************************************************/

int YAdd(int i, int a, int width)
{
	i += a;
	if (i < 0)
		i += width;
	if (i >= width)
		i -= width;
	return i;
}

/*********************************************************************************************
Function name: AdjecentColor
Input: Board, size and cell position
Output: Returns R or G according to most common color around the cell. 
The function operation: Scans around the cell, and checks which color is most common.
COMMENT: The function returnes N when there are equal # of red ang green cells around the cell. This is purly in order to get the program to compile correctly of the univercity's server,
		 as when I compile it using VS, it works fine even without it. It seems like VS can handle undefined cases (when count = 0) and returns NULL, but the Uni's servers return the first 
		 condition (R in this case) even if it's not true.
**********************************************************************************************/

char AdjacentColor(char board[MAX_HEIGHT][MAX_WIDTH], int i, int j, int height, int width)
{
	int k, l, count = 0, color;
	for (k = -1; k <= 1; k++)
		for (l = -1; l <= 1; l++)
		{
		if (k || l)
		{
			if (board[XAdd(i, k, height)][YAdd(j, l, width)] == 'R')
				count++;
			if (board[XAdd(i, k, height)][YAdd(j, l, width)] == 'G')
				count--;
		}
		
	}
	// If more R than G
	if (count > 0)
		return 'R';
	// If more G than R
	else if (count < 0)
		return 'G';
	// If equal - just so that the function will not return incorrect value.
	else
		return 'N';
}

/*********************************************************************************************
Function name: CheckVictory
Input: Board, size, max # of generations, current generation, doPrintBoard
Output:None
The function operation: Checks type of victory (or none) according to CheckVictoryCondition function.
						If a victory contition was met, check to see if board requires printing (according to doPrintBoard, in case a player won before board was printed),
						then print correct victory message and terminate the program.
**********************************************************************************************/

void CheckVictory(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long Gen, int doPrintBoard)
{
	int a;
	//type of victory (or none) according to CheckVictoryCondition.
	a = CheckVictoryCondition((char (*)[MAX_HEIGHT]) board, height, width, maxGen, Gen);
	switch (a)
	{
	case 1:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_HEIGHT]) board, height, width);
		printf("Game over! R is the winner :)\n");
		exit(0);
		break;
	case 2:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_HEIGHT]) board, height, width);
		printf("Game over! G is the winner :(\n");
		exit(0);
		break;
	case 3:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_HEIGHT]) board, height, width);
		printf("Game over! There is no winner :|\n");
		exit(0);
		break;
	// If no victory conditions were met.
	default:
		return;

	}
}

/*********************************************************************************************
Function name: CheckVictoryCondition
Input: Board, size, max # of generations, current generation.
Output: value according to type of victory.
The function operation: Checks the board to see if any victory conditios where met. Returns value accordingly:
															If gen limit reached, return:
																	1. If R is winner (R>G)
																	2. If G is winner (G>R)
																	3. If is a draw. (G=R)
															if gen limit not reached, return:
																	1. If R is winner (G=0)
																	2. If G is winner (R=0)
																	3. If is a draw (G&R=0)
																	0. If no conditions were met, continue the game.
**********************************************************************************************/

int CheckVictoryCondition(char board[MAX_HEIGHT][MAX_WIDTH], int height, int width, long maxGen, long Gen)
{
	int countG = 0, countR = 0, i, j;
	// Counts # of R and G cells on the board.
	for (i = 0; i < height; i++)
		for (j = 0;j < width;j++)
		{
			if (board[i][j] == 'R')
				countR++;
			if (board[i][j] == 'G')
				countG++;
		}
	// When gen count limit reached
	if (Gen == maxGen)
	{
		if (countR > countG)
			return 1;
		if (countR < countG)
			return 2;
		if (countR == countG)
			return 3;
	}
	//if gen count limit not reached, have another option to continue game.
	else
	{
		if (countR == 0 && countG == 0)
			return 3;
		else if (countG == 0)
			return 1;
		else if (countR == 0)
			return 2;
		else
			return 0;
	}

}