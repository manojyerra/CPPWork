#include "SudokuSolver.h"

SudokuSolver::SudokuSolver()
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			solution[i][j] = 0;
		}
	}
}

SudokuSolver::~SudokuSolver()
{
}

void SudokuSolver::SetRowCol(int row, int col, int num)
{
	solution[row][col] = num;
}

int SudokuSolver::GetNum(int row, int col)
{
	return solution[row][col];
}

bool SudokuSolver::Solve()
{
	bool cellWise = false;
	bool rowWise = false;
	bool colWise = false;
	bool blockWise = false;

	do
	{
		cellWise = SolveCellWise();
		//colWise = SolveColWise();
		rowWise = SolveRowWise();
		//blockWise = SolveBlockWise();
	}
	while(cellWise || rowWise || colWise || blockWise);

	return (AreAllGridsFilled());
}

bool SudokuSolver::AreAllGridsFilled()
{
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(solution[i][j] == 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool SudokuSolver::SolveCellWise()
{
	bool filledAtLeastOne = false;

	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(solution[row][col] == 0)
			{
				int num = SolveOneCell(row, col);

				if(num != 0)
				{
					filledAtLeastOne = true;
					solution[row][col] = num;
				}
			}
		}
	}

	return filledAtLeastOne;
}


bool SudokuSolver::SolveRowWise()
{
	bool returnValue = false;

	for(int row=0; row<9; row++)
	{
		FillPossibleValuesOfRow(row);
		FilterPossibleValues();
		
		int countFor1To9 = 0;
		int fillNum = 0;
		int fillColAt = 0;

		for(int i=0;i<9;i++)
		{
			countFor1To9 = 0;

			for(int j=0;j<9;j++)
			{
				if(possibleValuesOfR_C_B[i][j] != 0)
				{
					countFor1To9++;
					fillNum = possibleValuesOfR_C_B[i][j];
					fillColAt = i;
				}
			}

			if(countFor1To9 == 1)
			{
				solution[row][fillColAt] = fillNum;
				returnValue = true;
			}
		}
	}

	return returnValue;
}


bool SudokuSolver::SolveColWise()
{
	bool returnValue = false;

	for(int col=0; col<9; col++)
	{
		FillPossibleValuesOfCol(col);
		FilterPossibleValues();
		
		int countFor1To9 = 0;
		int fillNum = 0;
		int fillRowAt = 0;

		for(int i=0;i<9;i++)
		{
			countFor1To9 = 0;

			for(int j=0;j<9;j++)
			{
				if(possibleValuesOfR_C_B[i][j] != 0)
				{
					countFor1To9++;
					fillNum = possibleValuesOfR_C_B[i][j];
					fillRowAt = i;
				}
			}

			if(countFor1To9 == 1)
			{
				solution[fillRowAt][col] = fillNum;
				returnValue = true;
			}
		}
	}

	return returnValue;
}


bool SudokuSolver::SolveBlockWise()
{
	bool returnValue = false;

	for(int block=0; block<9; block++)
	{
		FillPossibleValuesOfBlock(block);
		FilterPossibleValues();

		int initRow = (block/3)*3;
		int initCol = (block%3)*3;

		int countFor1To9 = 0;
		int fillNum = 0;
		int fillBlockGridAt = 0;

		for(int i=0;i<9;i++)
		{
			countFor1To9 = 0;

			for(int j=0;j<9;j++)
			{
				if(possibleValuesOfR_C_B[i][j] != 0)
				{
					countFor1To9++;
					fillNum = possibleValuesOfR_C_B[i][j];
					fillBlockGridAt = i;
				}
			}

			if(countFor1To9 == 1)
			{
				int subBlockRow = fillBlockGridAt/3;
				int subBlockCol = fillBlockGridAt%3;

				solution[initRow+subBlockRow][initCol+subBlockCol] = fillNum;
				returnValue = true;
			}
		}
	}

	return returnValue;
}



void SudokuSolver::FilterPossibleValues()
{
	int num = 0;

	for(int rr=0;rr<9;rr++)
	{
		for(int cc=0;cc<9;cc++)
		{
			num = possibleValuesOfR_C_B[rr][cc];

			int count = 0;

			for(int r=0;r<9;r++){
				for(int c=0;c<9;c++){
					if(possibleValuesOfR_C_B[r][c] == num)
					{
						count++;
					}
				}
			}

			if(count > 1)
			{
				for(int r=0;r<9;r++)
				{
					for(int c=0;c<9;c++)
					{
						if(possibleValuesOfR_C_B[r][c] == num)
						{
							possibleValuesOfR_C_B[r][c] = 0;
						}
					}
				}
			}
		}
	}
}


void SudokuSolver::FillPossibleValuesOfRow(int rowNum)
{
	for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			possibleValuesOfR_C_B[r][c] = 0;
		}
	}

	for(int col=0; col<9; col++)
	{
		FillPossibleValueOfCell(rowNum, col);

		for(int i=0; i<9; i++)
		{
			possibleValuesOfR_C_B[col][i] = possibleValuesOfCell[i];
		}
	}
}


void SudokuSolver::FillPossibleValuesOfCol(int colNum)
{
	for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			possibleValuesOfR_C_B[r][c] = 0;
		}
	}

	for(int row=0; row<9; row++)
	{
		FillPossibleValueOfCell(row, colNum);

		for(int i=0; i<9; i++)
		{
			possibleValuesOfR_C_B[row][i] = possibleValuesOfCell[i];
		}
	}
}


void SudokuSolver::FillPossibleValuesOfBlock(int blockNum)
{
	for(int r=0;r<9;r++){
		for(int c=0;c<9;c++){
			possibleValuesOfR_C_B[r][c] = 0;
		}
	}

	int initRow = (blockNum/3)*3;
	int initCol = (blockNum%3)*3;

	int count = 0;

	for(int row=initRow; row<initRow+3; row++)
	{
		for(int col=initCol; col<initCol+3; col++)
		{
			FillPossibleValueOfCell(row, col);

			for(int i=0; i<9; i++)
				possibleValuesOfR_C_B[count][i] = possibleValuesOfCell[i];

			count++;
		}
	}
}


void SudokuSolver::FillPossibleValueOfCell(int row, int col)
{
	for(int loop=0; loop<9; loop++){
		possibleValuesOfCell[loop] = loop+1;
	}

	if(solution[row][col] != 0)
	{
		for(int loop=0; loop<9; loop++){
			possibleValuesOfCell[loop] = 0;
		}
		return;
	}

	for(int c=0;c<9;c++){
		if(solution[row][c] != 0){
			possibleValuesOfCell[solution[row][c]-1] = 0;
		}
	}

	for(int r=0;r<9;r++){
		if(solution[r][col] != 0){
			possibleValuesOfCell[solution[r][col]-1] = 0;
		}
	}

	int blockRow = (row/3)*3;
	int blockCol = (col/3)*3;

	for(int r=blockRow; r<blockRow+3; r++)
	{
		for(int c=blockCol; c<blockCol+3; c++)
		{
			if(solution[r][c] != 0)
			{
				possibleValuesOfCell[solution[r][c]-1] = 0;
			}
		}
	}
}


int SudokuSolver::SolveOneCell(int row, int col)
{
	FillPossibleValueOfCell(row, col);

	int count = 0;
	int resultNum = 0;

	for(int n=0; n<9; n++)
	{
		if(possibleValuesOfCell[n] != 0)
		{
			count++;
			resultNum = n;
		}
	}

	if(count == 1)
		return resultNum+1;

	return 0;
}

