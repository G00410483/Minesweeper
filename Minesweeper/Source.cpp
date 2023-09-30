#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <fstream>

#define ROWS 8
#define COLS 8	

//Variables controlled by user
int userRow;
int userCol;
int numOfUsers;

//Variables
char c = '-';
int score1 = 0;
int score2 = 0;
bool over = false;
int numOfMines;
int numID = 1;

//Arrays
char boardOutput[ROWS][COLS];
int boardValue[ROWS][COLS];
int randList[10];

//Declaring functions
void newGame();
void loadGame();
void userInput();
int countTheMines(int userRow, int userCol);
void displayGrid();
void singlePlayer();
void multiPlayer();
void generateRandom();

//Files
FILE* file1;
FILE* file2;
FILE* file3;

void main()
{
	int userChoice;
	srand(time(NULL));

	//Output
	printf("\n\t\tM I N E\tS W E E P E R\n\n");
	printf("-------------------------------------------------------------------\n");
	printf("SELECT ONE:\n\n");
	printf("1. NEW GAME\n");
	printf("2. LOAD GAME\n");
	scanf("%d", &userChoice);
	printf("-------------------------------------------------------------------\n");

	//If user starts a new game
	if (userChoice == 1)
	{
		newGame();
	}
	//Loading not working properly
	if (userChoice == 2)
	{
		loadGame();
	}
}
//User starts new game
void newGame()
{
	file3 = fopen("GameMode.txt", "w");
	printf("SELECT GAME MODE:\n\n");
	printf("1. SINGLE PLAYER\n");
	printf("2. MULTIPLAYER\n");
	scanf("%d", &numOfUsers);
	printf("-------------------------------------------------------------------\n");

	//Saving the game mode
	if (numOfUsers == 1)
	{
		fprintf(file3, "%d", numOfUsers);
	}
	else if (numOfUsers == 2)
	{
		fprintf(file3, "%d", numOfUsers);
	}
	fclose(file3);

	//Display the game grid
	for (int i = 0; i < ROWS; i++)
	{
		printf("|%d|\t", (i + 1));
		for (int j = 0; j < COLS; j++)
		{
			printf("%c\t", c);
			boardOutput[i][j] = c;
			boardValue[i][j] = numID;
			numID++;
		}
		printf("\n\n");
	}

	generateRandom();

	if (numOfUsers == 1)
	{
		singlePlayer();
	}
	else if (numOfUsers == 2)
	{
		multiPlayer();
	}
}
void loadGame()
{
	file1 = fopen("Output.txt", "r");
	file2 = fopen("Mines.txt", "r");
	file2 = fopen("GameMode.txt", "r");

	//Loading mines
	for (int i = 0; i < ROWS; i++)
	{
		fscanf(file2, "%d", &randList[i]);
	}
	/*
	//Coulnd't get to load properly
	//Loading board
	for (int i = 0; i < ROWS; i++)
	{
		printf("|%d|\t", (i + 1));
		for (int j = 0; j < COLS; j++)
		{
			fscanf(file1, "%d", &boardOutput[i][j]);
			printf("%d\t", boardOutput[i][j]);	
		}
		printf("\n\n");
	}
	//Loading game mode
	fscanf(file3, "%d", &numOfUsers);
	if (numOfUsers == 1)
	{
		singlePlayer();
	}
	else if (numOfUsers == 2)
	{
		multiPlayer();
	}
	*/
}
//Generate 10 random numbers
void generateRandom()
{
	file2 = fopen("Mines.txt", "w");
	
	for (int i = 0; i < 10; i++)
	{
		randList[i] = (rand() % 64) + 1;
		fprintf(file2, "%d\n", randList[i]);
	}
	fclose(file2);
}
//User inputs rows and cols
void userInput()
{
	//User enters row number
	printf("-------------------------------------------------------------------\n\n");
	printf("\tEnter row number (1-8): ");
	scanf("%d", &userRow);

	//User enters column number
	printf("\tEnter column number (1-8): ");
	scanf("%d", &userCol);
	printf("-------------------------------------------------------------------\n\n");

	countTheMines(userRow, userCol);
}
//Counts the mines
int countTheMines(int userRow, int userCol)
{
	for (int i = 0; i < 10; i++)
	{
		//Counting mines in case row and col number is NOT minimum or maximum (1 or 8)
		if (userRow != 1 && userRow != 8 && userCol != 1 && userCol != 8)
		{
			//Counting mines in the row above
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 9 || randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 7)
			{
				numOfMines++;
			}
			//Counting mines in the row under
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 9 || randList[i] == boardValue[userRow - 1][userCol - 1] + 8 || randList[i] == boardValue[userRow - 1][userCol - 1] + 7)
			{
				numOfMines++;
			}
			//Counting mines in the same row
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1 || randList[i] == boardValue[userRow - 1][userCol - 1] + 1)
			{
				numOfMines++;
			}
		}

		//Counting mines in case user selects top left corner
		if (userRow == 1 && userCol == 1)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 1 || randList[i] == boardValue[userRow - 1][userCol - 1] + 8 || randList[i] == boardValue[userRow - 1][userCol - 1] + 9)
			{
				numOfMines++;
			}
		}
		//Counting mines in case user selects top right corner
		if (userRow == 1 && userCol == 8)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1 || randList[i] == boardValue[userRow - 1][userCol - 1] + 7 || randList[i] == boardValue[userRow - 1][userCol - 1] + 8)
			{
				numOfMines++;
			}
		}
		//Counting mines in case user selects bottom left corner
		if (userRow == 8 && userCol == 8)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1 || randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 9)
			{
				numOfMines++;
			}
		}
		//Counting mines in case user selects bottom right corner
		if (userRow == 8 && userCol == 1)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 1 || randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 7)
			{
				numOfMines++;
			}
		}
		//Counting mines if user selects first row and NOT first or last column
		if (userRow == 1 && userCol != 1 && userCol != 8)
		{
			//Coutining mines in the same row
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1 || randList[i] == boardValue[userRow - 1][userCol - 1] + 1)
			{
				numOfMines++;
			}
			//Counting mines in the row under
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 9 || randList[i] == boardValue[userRow - 1][userCol - 1] + 8 || randList[i] == boardValue[userRow - 1][userCol - 1] + 7)
			{
				numOfMines++;
			}
		}
		//Counting mines if user selects last row and NOT first or last column
		if (userRow == 8 && userCol != 1 && userCol != 8)
		{
			//Counting mines in the same row
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1 || randList[i] == boardValue[userRow - 1][userCol - 1] + 1)
			{
				numOfMines++;
			}
			//Counting mines in the row above
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 9 || randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 7)
			{
				numOfMines++;
			}
		}
		//Counting mines if user selects first column and NOT first or last row
		if (userCol == 1 && userRow != 1 && userRow != 8)
		{
			//Coutining mines in the row above
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 7)
			{
				numOfMines++;
			}
			//Counting mines in the same row 
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 1)
			{
				numOfMines++;
			}
			//Counting mines in the row under
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 8 || randList[i] == boardValue[userRow - 1][userCol - 1] + 9)
			{
				numOfMines++;
			}
		}
		//Counting mines if user selects last column and NOT first or last row
		if (userCol == 8 && userRow != 1 && userRow != 8)
		{
			//Coutining mines in the row above
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 8 || randList[i] == boardValue[userRow - 1][userCol - 1] - 9)
			{
				numOfMines++;
			}
			//Counting mines in the same row 
			if (randList[i] == boardValue[userRow - 1][userCol - 1] - 1)
			{
				numOfMines++;
			}
			//Counting mines in the row under
			if (randList[i] == boardValue[userRow - 1][userCol - 1] + 8 || randList[i] == boardValue[userRow - 1][userCol - 1] + 7)
			{
				numOfMines++;
			}
		}
	}
	return numOfMines;
}
// Displays new game grid
void displayGrid()
{
	file1 = fopen("Output.txt", "w");

	for (int i = 0; i < ROWS; i++)
	{
		printf("|%d|\t", (i + 1));
		for (int j = 0; j < COLS; j++)
		{
			if (boardOutput[i][j] != c && boardOutput[i][j] != 0)
			{
				if (boardOutput[i][j] == boardOutput[userRow][userRow])
				{
					boardOutput[i][j] = numOfMines;
				}
				printf("%d\t", boardOutput[i][j]);
				fprintf(file1, "%d", boardOutput[i][j]);
			}
			else
			{
				printf("%c\t", c);
				fprintf(file1, "%c", c);
			}
		}
		printf("\n\n");
	}
	fclose(file1);
}
//SINGLEPLAYER
void singlePlayer()
{
	while (over == false && score1 < 100)
	{
		numOfMines = 0;

		userInput();

		//Checking if user selected square with mine
		for (int i = 0; i < 10; i++)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1])
			{
				over = true;
				printf("Game Over!\nYou Stepped on the Mine!\n");
			}
		}
		//If user reaches score 100
		if (score1 >= 100)
		{
			printf("Game Over!\nYou Won!\n");
		}
		if (over == false)
		{
			//For each square revealed user get 10 points
			score1 += 10;

			//Assignings number of mines for selected square
			boardOutput[userRow - 1][userCol - 1] = numOfMines;

			displayGrid();

		}
		printf("YOUR SCORE: %d\n\n\n", score1);
	}
	//If user scores 100- 10 squares revealed
	if (score1 >= 100)
	{
		printf("YOU WON !");
	}
}
//MULTIPLAYER
void multiPlayer()
{
	while (over == false && (score1 < 80 || score2 < 80))
	{
		//PLAYER 1
		numOfMines = 0;

		printf("PLAYER 1\n");
		userInput();

		//Checking if user selected square with mine
		for (int i = 0; i < 10; i++)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1])
			{
				over = true;
				printf("Game Over!\nYou Stepped on the Mine!\nPlayer 2 won!\n");
			}
		}
		//If user reaches score 100
		if (score1 >= 80)
		{
			printf("Game Over!\nPlayer 1 won!\n");
		}
		if (over == false)
		{
			//For each square revealed user get 10 points
			score1 += 10;

			//Assignings number of mines for selected square
			boardOutput[userRow - 1][userCol - 1] = numOfMines;

			displayGrid();

		}
		printf("SCORE PLAYER 1: %d\n", score1);
		printf("SCORE PLAYER 2: %d\n\n\n", score2);

		//PLAYER 2
		numOfMines = 0;

		printf("PLAYER 2\n");
		userInput();

		//Checking if user selected square with mine
		for (int i = 0; i < 10; i++)
		{
			if (randList[i] == boardValue[userRow - 1][userCol - 1])
			{
				over = true;
				printf("Game Over!\nYou Stepped on the Mine!\nPlayer 1 won!\n");
			}
		}
		//If user reaches score 100
		if (score1 >= 80)
		{
			printf("Game Over!\nPlayer 2 Won!\n");
		}
		if (over == false)
		{
			//For each square revealed user get 10 points
			score2 += 10;

			//Assignings number of mines for selected square
			boardOutput[userRow - 1][userCol - 1] = numOfMines;

			displayGrid();

		}
		printf("SCORE PLAYER 1: %d\n", score1);
		printf("SCORE PLAYER 2: %d\n\n\n", score2);

	}
	//If user scores 80- 8 squares revealed
	if (score1 >= 80 || score2 >= 80)
	{
		if (score1 > score2)
		{
			printf("PLAYER 1 WON !");
		}
		else
		{
			printf("PLAYER 2 WON !");
		}
	}
}
