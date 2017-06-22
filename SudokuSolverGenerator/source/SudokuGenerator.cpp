#include "SudokuGenerator.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>


SudokuGenerator::SudokuGenerator()
{
	int localAllSudokus[NUM_ALL_SUDOKUS][9][9]=
	{
		{
			{4,8,3, 9,5,1, 2,6,7},
			{2,6,9, 7,8,4, 5,3,1},
			{5,7,1, 6,3,2, 4,9,8},

			{7,3,5, 4,1,6, 9,8,2},
			{8,9,6, 5,2,3, 7,1,4},
			{1,2,4, 8,9,7, 3,5,6},

			{6,5,2, 3,4,8, 1,7,9},
			{9,1,7, 2,6,5, 8,4,3},
			{3,4,8, 1,7,9, 6,2,5}
		},
		{
			{2,9,7, 1,8,4, 3,6,5},
			{1,5,4, 9,6,3, 2,7,8},
			{6,8,3, 2,5,7, 4,9,1},

			{4,1,5, 7,3,8, 6,2,9},
			{9,6,2, 4,1,5, 7,8,3},
			{7,3,8, 6,2,9, 1,5,4},

			{3,2,6, 8,9,1, 5,4,7},
			{5,4,9, 3,7,6, 8,1,2},
			{8,7,1, 5,4,2, 9,3,6}
		},
		{
			{1,5,4, 6,7,3, 9,8,2},
			{3,9,7, 1,2,8, 6,4,5},
			{6,8,2, 5,4,9, 3,7,1},

			{5,7,9, 3,8,6, 1,2,4},
			{8,6,3, 2,1,4, 7,5,9},
			{4,2,1, 7,9,5, 8,6,3},

			{2,1,6, 4,3,7, 5,9,8},
			{9,3,5, 8,6,2, 4,1,7},
			{7,4,8, 9,5,1, 2,3,6}
		}
	};

	for(int num=0;num<NUM_ALL_SUDOKUS;num++)
		for(int r=0;r<9;r++)
			for(int c=0;c<9;c++)
				allSudokus[num][r][c] = localAllSudokus[num][r][c];

	_sudokuSolver = new SudokuSolver();
}

SudokuGenerator::~SudokuGenerator()
{
}

void SudokuGenerator::GenerateSudoku(char* filePathToSaveSudoku)
{
	int num = rand()%NUM_ALL_SUDOKUS;

	for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			question[r][c] = allSudokus[num][r][c];
		}
	}

	Shuffle();

	for(int i=0;i<300;i++)
	{
		int row = 0;
		int col = 0;
		int num = 0;

		int random = (rand() + GetTickCount()) % 81;
		int count = 0;

		do
		{
			for(int rr=0; rr<9; rr++)
			{
				if(count > random)
					break;

				for(int cc=0;cc<9;cc++)
				{
					if(question[rr][cc] != 0)
					{
						if(count == random)
						{
							num = question[rr][cc];
							row = rr;
							col = cc;
							count++;
							break;
						}
						count++;
					}
				}
			}
		}while(num == 0);

		question[row][col] = 0;

		for(int r=0;r<9;r++){
			for(int c=0;c<9;c++){
				_sudokuSolver->SetRowCol(r, c, question[r][c]);
			}
		}

		if(!_sudokuSolver->Solve())
			question[row][col] = num;
	}

	int totalNum = 0;

	for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			if(question[r][c] != 0)
			{
				totalNum++;
			}
		}
	}


	FILE* fp;
	fp = fopen(filePathToSaveSudoku, "w");

	for(int r=0;r<9;r++)
	{
		for(int c=0;c<9;c++)
		{
			fprintf(fp,"%d,",question[r][c]);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);
}


void SudokuGenerator::Shuffle()
{
	//shuffling rows and cols 10 times...

	int row1 = rand()%3;
	int row2 = rand()%3;

	for(int c=0;c<9;c++)
	{
		int temp = question[row1][c];
		question[row1][c] = question[row2][c];
		question[row2][c] = temp;
	}

	int col1 = rand()%3;
	int col2 = rand()%3;

	for(int r=0;r<9;r++)
	{
		int temp = question[r][col1];
		question[r][col1] = question[r][col2];
		question[r][col2] = temp;
	}
}
