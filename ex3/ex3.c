
#include <stdio.h>
#include <stdlib.h>



#define MAX_WIDTH 70
#define MAX_HEIGHT 70
#define MIN_WIDTH 10
#define MIN_HEIGHT 10
#define CLR_AI 'G'
#define CLR_PLYR 'R'


void GameStart(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height, int* maxGen, int* Gen);
void InitializeBoard(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height);
void GetDimensions(int* width, int* height);
void LiveCells(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
int IsCellPosValid(int i, int j, int width, int height, int color, char board[MAX_WIDTH][MAX_HEIGHT]);
void PrintBoard(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
void GamePlay(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen);
void TurnPlayer(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen);
void TurnAI(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen);
void AICellChoice(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
void AdvanceGen(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
char AdjacentColor(char board[MAX_WIDTH][MAX_HEIGHT], int i, int j, int width, int height);
long int GetMaxGen(int* maxGen);
void CheckVictory(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int Gen, int doPrintBoard);




int main()
{
	char board[MAX_WIDTH][MAX_HEIGHT];
	int width, height;
	int maxGen = -1, Gen = 0;

	GameStart((char (*)[MAX_HEIGHT]) board, &width, &height, &maxGen, &Gen);
	GamePlay((char (*)[MAX_WIDTH]) board, width, height, maxGen, &Gen);


	return 0;
}

void GameStart(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height, int* maxGen, int* Gen)
{
	printf("Welcome to the game of life!\nSettings:\n");
	InitializeBoard((char (*)[MAX_WIDTH]) board, width, height);
	CheckVictory((char (*)[MAX_WIDTH]) board, *width, *height, *maxGen, *Gen, -10);
	GetMaxGen(maxGen);
	AdvanceGen((char (*)[MAX_WIDTH]) board, *width, *height);
	printf("Welcome to the game of life!\nThis is the initial board:\n");
	PrintBoard((char (*)[MAX_WIDTH]) board, *width, *height);
	CheckVictory((char (*)[MAX_WIDTH]) board, *width, *height, *maxGen, *Gen, -10);

}

void GetDimensions(int* width, int* height)
{
	do
	{
		printf("Enter width (10-70):\n");
		scanf("%d", width);
	} while (*width > MAX_WIDTH || *width < MIN_WIDTH);
	do
	{
		printf("Enter height (10-70):\n");
		scanf("%d", height);
	} while (*height > MAX_HEIGHT || *height < MIN_HEIGHT);
	return;

}

void InitializeBoard(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height)
{
	int i, j;
	for (i = 0; i < MAX_WIDTH; i++)
		for (j = 0;j < MAX_HEIGHT;j++)
			board[i][j] = '-';
	GetDimensions(width, height);
	LiveCells((char (*)[MAX_WIDTH]) board, *width ,*height);
	PrintBoard((char (*)[MAX_WIDTH]) board, *width, *height);
	return;
}

void LiveCells(char board[MAX_WIDTH][MAX_HEIGHT] ,int width ,int height)
{
	int i, j, n, cellCount, accepted;
	char color;
	int maxCellCount = width*height;
	do
	{
		printf("Enter number of living cells (0-%d):\n", maxCellCount);
		scanf("%d", &cellCount);
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
			accepted = IsCellPosValid(i, j, width, height, color ,(char (*)[MAX_WIDTH]) board);
		} while (accepted != 1);
		board[i][j] = color;
	}
	printf("\n");
	return;
}

int IsCellPosValid(int i, int j, int width, int height, int color, char board[MAX_WIDTH][MAX_HEIGHT])
{
	int valid = 0;
	if (i < width && i >= 0 && j < height && j >= 0)
		if (color == 'R' || color == 'G')
			if (board[i][j] == '-')
				valid = 1;
	return valid;
}

void PrintBoard(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
{
	int i, j;

	for (i = 0; i < width; i++)
	{
		for (j = 0;j < height;j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
	printf("\n");
	return;
}

long int GetMaxGen(int* maxGen)
{
	printf("Enter number of generations(>=0):\n");
	scanf("%d", maxGen);
	printf("\n");

}

void GamePlay(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen)
{
	int i;
	for (i = 0; i < maxGen; i++)
	{
		if (i % 2 == 0)
		{
			printf("R is playing\n");
			TurnPlayer((char (*)[MAX_WIDTH]) board, width, height, maxGen, Gen);
		}
		else
		{
			printf("G is playing\n");
			TurnAI((char (*)[MAX_WIDTH]) board, width, height, maxGen, Gen);
		}
	}
	return;
}

void TurnPlayer(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen)
{
	int i, j, doPrintBoard = *Gen;
	printf("x y:\n");
	scanf("%d %d", &i, &j);
	board[i][j] = 'R';
	CheckVictory((char(*)[MAX_WIDTH]) board, width, height, maxGen, *Gen, doPrintBoard);
	*Gen += 1;
	AdvanceGen((char (*)[MAX_WIDTH]) board, width, height);
	PrintBoard((char (*)[MAX_WIDTH]) board, width, height);
	CheckVictory((char(*)[MAX_WIDTH]) board, width, height, maxGen, *Gen, doPrintBoard);

	return;
}

void TurnAI(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int* Gen)
{
	int doPrintBoard = *Gen;
	AICellChoice((char (*)[MAX_WIDTH]) board, width, height);
	printf("\n");
	CheckVictory((char(*)[MAX_WIDTH]) board, width, height, maxGen, *Gen, doPrintBoard);
	AdvanceGen((char (*)[MAX_WIDTH]) board, width, height);
	*Gen += 1;
	PrintBoard((char (*)[MAX_WIDTH]) board, width, height);
	CheckVictory((char(*)[MAX_WIDTH]) board, width, height, maxGen, *Gen, doPrintBoard);

	return;
}

void AICellChoice(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
{
	int i, j, a;
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
		{
			a = AdjacentTo((char (*)[MAX_WIDTH]) board, i, j, width, height);
			if (board[i][j] == 'R' && a > 1 && a < 4)
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
		{
			a = AdjacentTo((char (*)[MAX_WIDTH]) board, i, j, width, height);
			if (board[i][j] == '-' && AdjacentColor((char (*)[MAX_WIDTH]) board, i, j, width, height) == 'R' && a > 1 && a < 4)
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
		{
			a = AdjacentTo((char (*)[MAX_WIDTH]) board, i, j, width, height);
			if (board[i][j] == 'R')
			{
				printf("%d %d", i, j);
				board[i][j] = 'G';
				return;
			}
		}

}

void AdvanceGen(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
{
	int i, j, a;
	char newBoard[MAX_WIDTH][MAX_HEIGHT];
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
	{
		a = AdjacentTo((char (*)[MAX_WIDTH]) board, i, j, width, height);
		if (a == 2)
			newBoard[i][j] = board[i][j];
		if (a == 3)
			if (board[i][j]=='-')
				newBoard[i][j] = AdjacentColor((char (*)[MAX_WIDTH]) board, i, j, width, height);
			else
				newBoard[i][j] = board[i][j];
		
		if (a < 2 || a > 3)
			newBoard[i][j] = '-';


	}
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
			board[i][j] = newBoard[i][j];


	return;
}

int AdjacentTo(char board[MAX_WIDTH][MAX_HEIGHT], int i, int j, int width, int height)
{
	int k, l, count = 0;
	for (k = -1; k <= 1; k++)
	{
		for (l = -1; l <= 1; l++)
		{
			if (k || l)
				if (board[XAdd(i, k, width)][YAdd(j, l, height)] != '-')
					count++;
		}
	}
	return count;
}

int XAdd(int i, int a, int width)
{
	i += a;
	if (i < 0) 
		i += width;
	if (i >= width) 
		i -= width;
	return i;
}

int YAdd(int i, int a, int height)
{
	i += a;
	if (i < 0)
		i += height;
	if (i >= height)
		i -= height;
	return i;
}

char AdjacentColor(char board[MAX_WIDTH][MAX_HEIGHT], int i, int j, int width, int height)
{
	int k, l, count = 0, color;
	for (k = -1; k <= 1; k++)
		for (l = -1; l <= 1; l++)
		{
		if (k || l)
		{
			if (board[XAdd(i, k, width)][YAdd(j, l, height)] == 'R')
				count++;
			if (board[XAdd(i, k, width)][YAdd(j, l, height)] == 'G')
				count--;
		}
		
	}
	if (count > 0)
		return 'R';
	else if (count < 0)
		return 'G';
	else
		return 'N';
}

void CheckVictory(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int Gen, int doPrintBoard)
{
	int a;
	a = CheckVictoryCondition((char (*)[MAX_WIDTH]) board, width, height, maxGen, Gen);
	switch (a)
	{
	case 1:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_WIDTH]) board, width, height);
		printf("Game over! R is the winner :)\n");
		exit(0);
		break;
	case 2:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_WIDTH]) board, width, height);
		printf("Game over! G is the winner :(\n");
		exit(0);
		break;
	case 3:
		if (doPrintBoard == Gen)
			PrintBoard((char(*)[MAX_WIDTH]) board, width, height);
		printf("Game over! There is no winner :|\n");
		exit(0);
		break;
	default:
		return;

	}
}

int CheckVictoryCondition(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen, int Gen)
{
	int countG = 0, countR = 0, i, j;

	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
		{
			if (board[i][j] == 'R')
				countR++;
			if (board[i][j] == 'G')
				countG++;
		}
	if (Gen == maxGen)
	{
		if (countR > countG)
			return 1;
		if (countR < countG)
			return 2;
		if (countR == countG)
			return 3;
	}
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