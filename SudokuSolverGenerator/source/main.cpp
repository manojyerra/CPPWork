#include "SudokuSolver.h"
#include "SudokuGenerator.h"
#include <windows.h>

void SolveSudoku(int arr[][9]);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	int arr[9][9]=
	{
		{0,0,3, 9,0,0, 0,6,0},
		{2,0,0, 7,0,0, 0,3,0},
		{0,7,0, 6,0,2, 0,0,0},

		{7,0,0, 0,1,0, 0,8,2},
		{0,9,0, 0,0,3, 7,0,0},
		{1,0,0, 0,9,0, 0,5,6},

		{0,5,0, 3,0,8, 0,0,0},
		{9,0,0, 2,0,0, 0,4,0},
		{0,0,8, 1,0,0, 0,2,0}
	};

	SolveSudoku(arr);

	SudokuGenerator* sudokuGenerator = new SudokuGenerator();
	sudokuGenerator->GenerateSudoku("NewSudoku.txt");
}

void SolveSudoku(int arr[][9])
{
	SudokuSolver* sudokuSolver = new SudokuSolver();

	for(int r=0;r<9;r++)
		for(int c=0;c<9;c++)
			sudokuSolver->SetRowCol(r, c, arr[r][c]);

	bool solved = sudokuSolver->Solve();

	if(solved)
	{
		for(int r=0;r<9;r++)
			for(int c=0;c<9;c++)
				arr[r][c] = sudokuSolver->GetNum(r, c);
	}

	delete sudokuSolver;
}
