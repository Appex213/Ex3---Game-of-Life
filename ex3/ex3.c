
#include <stdio.h>



#define MAX_WIDTH 70
#define MAX_HEIGHT 70
#define MIN_WIDTH 10
#define MIN_HEIGHT 10
#define CLR_AI 'G'
#define CLR_PLYR 'R'


void GameStart(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height);
void InitializeBoard(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height);
void GetDimensions(int* width, int* height);
void LiveCells(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
int IsCellPosValid(int i, int j, int width, int height, int color);
void PrintBoard(const board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
void GamePlay(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen);
void ProcessBoard(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
void AdvanceGen(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height);
char AdjacentColor(char board[MAX_WIDTH][MAX_HEIGHT], int i, int j, int width, int height);





int main()
{
	char board[MAX_WIDTH][MAX_HEIGHT];
	int width, height;
	int maxGen;

	GameStart(board, &width, &height, &maxGen);
	GamePlay(board, width, height, maxGen);


	_getch();

	return 0;
}

void GameStart(char board[MAX_WIDTH][MAX_HEIGHT], int* width, int* height, int* maxGen)
{
	printf("Welcome to the game of life!\nSettings:\n");
	InitializeBoard(board, width, height);
	GetMaxGen(maxGen);
	ProcessBoard(board, *width, *height);
	printf("Welcome to the game of life!\nThis is the initial board :\n");
	PrintBoard(board, *width, *height);

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
	LiveCells(board, *width ,*height);
	PrintBoard(board, *width, *height);
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
	//		i--, j--;
			if (color == 'g')
					color = 'G';
			if (color == 'r')
					color = 'R';
			accepted = IsCellPosValid(i, j, width, height, color ,board);
			printf("a=%d\n", accepted);
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

void PrintBoard(const char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
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
	printf("Enter number of generations(>0):\n");
	scanf("%d", maxGen);

}

void GamePlay(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height, int maxGen)
{
	ProcessBoard(board, width, height);

	return;
}

void ProcessBoard(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
{
	AdvanceGen(board, width, height);

	return;
}

void AdvanceGen(char board[MAX_WIDTH][MAX_HEIGHT], int width, int height)
{
	int i, j, a;
	char newBoard[MAX_WIDTH][MAX_HEIGHT];
	for (i = 0; i < width; i++)
		for (j = 0;j < height;j++)
	{
		a = AdjacentTo(board, i, j, width, height);
		if (a == 2)
			newBoard[i][j] = board[i][j];
		if (a == 3)
			if (board[i][j]=='-')
				newBoard[i][j] = AdjacentColor(board, i, j, width, height);
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
	for (k = -1 ; k <= 1 ; k++) 
		for (l = -1 ; l <= 1 ; l++)
	{
		if (k != l)
			if (board[XAdd(i,k,width)][YAdd(j,l,height)] != '-')
				count++;
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
		if (k != l)
		{
			if (board[XAdd(i, k, width)][YAdd(j, l, height)] = 'R')
				count++;
			if (board[XAdd(i, k, width)][YAdd(j, l, height)] = 'G')
				count--;
		}
		
	}
	if (count == 1)
		return 'R';
	if (count == -1)
		return 'G';
}