#ifndef SUDOKU_SOLVER
#define SUDOKU_SOLVER
#pragma once

class SudokuSolver
{
private:
	int solution[9][9];
	int possibleValuesOfCell[9];
	int possibleValuesOfR_C_B[9][9]; // we can fill possible values of row or coloumn or block in this array.

	bool SolveCellWise();
	bool SolveRowWise();
	bool SolveColWise();
	bool SolveBlockWise();
	int SolveOneCell(int row, int col);

	bool AreAllGridsFilled();

	void FillPossibleValueOfCell(int row, int col);
	void FillPossibleValuesOfRow(int rowNum);
	void FillPossibleValuesOfCol(int colNum);
	void FillPossibleValuesOfBlock(int blockNum);

	void FilterPossibleValues();

public:
	SudokuSolver();
	~SudokuSolver();

	void SetRowCol(int row, int col, int num);
	int GetNum(int row, int col);

	bool Solve();
};

#endif
