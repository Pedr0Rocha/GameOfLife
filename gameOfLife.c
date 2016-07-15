#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 50

int countAliveNeighbors(int board[N][N], int i, int j) {
	int count = 0;
	if (i + 1 < N && board[i+1][j] == 1) 
		count++;
	if (i - 1 >= 0 && board[i-1][j] == 1) 
		count++;
	if (j + 1 < N && board[i][j+1] == 1) 
		count++;
	if (j - 1 >= 0 && board[i][j-1] == 1) 
		count++;
	if ((i + 1 < N && j + 1 < N) && board[i+1][j+1] == 1) 
		count++;
	if ((i + 1 < N && j - 1 >= 0) && board[i+1][j-1] == 1) 
		count++;
	if ((i - 1 >= 0 && j + 1 < N) && board[i-1][j+1] == 1) 
		count++;
	if ((i - 1 >= 0 && j - 1 >= 0) && board[i-1][j-1] == 1) 
		count++;
	return count;
}

void printBoard(int board[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (board[i][j] == 1) 
				printf("\033[0;34m\u25A0 \033[0m");
			else
				printf("\033[0;37m\u25A0 \033[0m");
		}
		printf("\n");
	}
}

void buildGlider(int board[N][N]) {
	board[N/2][N/2] = 1;
	board[N/2][(N/2)+1] = 1;
	board[N/2][(N/2)+2] = 1;
	board[(N/2)-1][(N/2)+2] = 1;
	board[(N/2)-2][(N/2)+1] = 1;
}

void buildGliderGun(int board[N][N]) {
	board[1][5] = 1;
	board[1][6] = 1;
	board[2][5] = 1;
	board[2][6] = 1;
	board[11][5] = 1;
	board[11][6] = 1;
	board[11][7] = 1;
	board[12][4] = 1;
	board[12][8] = 1;
	board[13][3] = 1;
	board[13][9] = 1;
	board[14][3] = 1;
	board[14][9] = 1;
	board[15][6] = 1;
	board[16][4] = 1;
	board[16][8] = 1;
	board[17][5] = 1;
	board[17][6] = 1;
	board[17][7] = 1;
	board[18][6] = 1;
	board[21][3] = 1;
	board[21][4] = 1;
	board[21][5] = 1;
	board[22][3] = 1;
	board[22][4] = 1;
	board[22][5] = 1;
	board[23][2] = 1;
	board[23][6] = 1;
	board[25][1] = 1;
	board[25][2] = 1;
	board[25][6] = 1;
	board[25][7] = 1;
	board[35][3] = 1;
	board[35][4] = 1;
	board[36][3] = 1;
	board[36][4] = 1;
	board[35][22] = 1;
	board[35][23] = 1;
	board[35][25] = 1;
	board[36][22] = 1;
	board[36][23] = 1;
	board[36][25] = 1;
	board[36][26] = 1;
	board[36][27] = 1;
	board[37][28] = 1;
	board[38][22] = 1;
	board[38][23] = 1;
	board[38][25] = 1;
	board[38][26] = 1;
	board[38][27] = 1;
	board[39][23] = 1;
	board[39][25] = 1;
	board[40][23] = 1;
	board[40][25] = 1;
	board[41][24] = 1;
}

void initBoard(int board[N][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			//board[i][j] = rand() % 2;
			board[i][j] = 0;
}

int main() {
	int seed = time(NULL);
	srand(seed);
	printf("Seed -> %d\n\n", seed);

	int board[N][N];
	int boardModifications[N][N];	
	initBoard(board);
	initBoard(boardModifications);

	//buildGlider(board);
	buildGliderGun(board);
	int gameLoop = 0;
	while (gameLoop++ < 1000) {
		printf("Game of Life - Cicle %d\n", gameLoop);
		printBoard(board);
		usleep(9000);
		system("clear");
		for (int i = 0; i < N; i++) 
			for (int j = 0; j < N; j++) {
				int cellNeighbors = countAliveNeighbors(board, i, j);
				boardModifications[i][j] = cellNeighbors;
			}
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++) {
				int isAlive = board[i][j];
				if (isAlive) {
					if (boardModifications[i][j] < 2) 
						board[i][j] = 0;
					if (boardModifications[i][j] >= 4) 
						board[i][j] = 0;
				} else 
					if (boardModifications[i][j] == 3) 
						board[i][j] = 1;	
			}
		initBoard(boardModifications);
	}
}