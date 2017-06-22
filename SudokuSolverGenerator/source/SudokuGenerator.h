#ifndef SUDOKU_GENERATOR
#define SUDOKU_GENERATOR

#include "SudokuSolver.h"

class SudokuGenerator
{
private:
	static const int NUM_ALL_SUDOKUS = 3;
	int allSudokus[NUM_ALL_SUDOKUS][9][9];
	int question[9][9];

	SudokuSolver* _sudokuSolver;
	void Shuffle();

public:
	SudokuGenerator();
	~SudokuGenerator();

	void GenerateSudoku(char* filePathToSaveSudoku);
};

#endif
