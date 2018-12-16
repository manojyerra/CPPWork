#include "SaveManager.h"
#include "GameInfo.h"
#include "Platform.h"

SaveManager* SaveManager::_ref = 0;

SaveManager::SaveManager()
{
	_saveData = NULL;
	ReadSave();
}

SaveManager* SaveManager::GetInstance()
{
	if(_ref == 0)
		_ref = new SaveManager();
	return _ref;
}

void SaveManager::ReadSave()
{
	if(_saveData != NULL)
		delete _saveData;

	_saveData = new SaveData();

	int result = Platform::GetPlatform()->GetSaveData(_saveData, sizeof(SaveData));

	if(result == 0)
		FillDefaultValues();
}

void SaveManager::FillDefaultValues()
{
	_saveData->TotalLevels_Num3x3 = (int)TOTAL_LEVELS_NUM_3x3;

	for(int i=0; i<_saveData->TotalLevels_Num3x3; i++)
	{
		_saveData->NumStarsArray_Num3x3[i] = 0;
		_saveData->TimeArray_Num3x3[i] = 0;
		_saveData->NumMovesArray_Num3x3[i] = 0;
	}

	_saveData->LastUnlockedLevel_Num3x3 = 1;
	_saveData->CurrLevel_Num3x3 = 1;


	_saveData->TotalLevels_Num4x4 = (int)TOTAL_LEVELS_NUM_4x4;

	for(int i=0; i<_saveData->TotalLevels_Num4x4; i++)
	{
		_saveData->NumStarsArray_Num4x4[i] = 0;
		_saveData->TimeArray_Num4x4[i] = 0;
		_saveData->NumMovesArray_Num4x4[i] = 0;
	}

	_saveData->LastUnlockedLevel_Num4x4 = 1;
	_saveData->CurrLevel_Num4x4 = 1;


	_saveData->TotalLevels_Num5x5 = (int)TOTAL_LEVELS_NUM_5x5;

	for(int i=0; i<_saveData->TotalLevels_Num5x5; i++)
	{
		_saveData->NumStarsArray_Num5x5[i] = 0;
		_saveData->TimeArray_Num5x5[i] = 0;
		_saveData->NumMovesArray_Num5x5[i] = 0;
	}

	_saveData->LastUnlockedLevel_Num5x5 = 1;
	_saveData->CurrLevel_Num5x5 = 1;

	
	_saveData->GameID = NUM_3x3;
}

void SaveManager::SaveGame()
{
	Platform::GetPlatform()->SetSaveData(_saveData, sizeof(SaveData));
}

SaveData* SaveManager::GetSaveData()
{
	return _saveData;
}

void SaveManager::SetGameID(int gameID)
{
	_saveData->GameID = gameID;
}

int SaveManager::GetGameID()
{
	return _saveData->GameID;
}


//***************************************** Level Data Saving... ******************************************//

int SaveManager::GetNumTotalLevels()
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->TotalLevels_Num3x3;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->TotalLevels_Num4x4;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->TotalLevels_Num5x5;
	}

	return 0;
}

void SaveManager::SetCurrLevel(int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		_saveData->CurrLevel_Num3x3 = levelNum;
		if(_saveData->CurrLevel_Num3x3 > _saveData->LastUnlockedLevel_Num3x3)
			SetLastUnlockedLevel(_saveData->CurrLevel_Num3x3);
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		_saveData->CurrLevel_Num4x4 = levelNum;
		if(_saveData->CurrLevel_Num4x4 > _saveData->LastUnlockedLevel_Num4x4)
			SetLastUnlockedLevel(_saveData->CurrLevel_Num4x4);
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		_saveData->CurrLevel_Num5x5 = levelNum;
		if(_saveData->CurrLevel_Num5x5 > _saveData->LastUnlockedLevel_Num5x5)
			SetLastUnlockedLevel(_saveData->CurrLevel_Num5x5);
	}
}

int SaveManager::GetCurrLevel()
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->CurrLevel_Num3x3;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->CurrLevel_Num4x4;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->CurrLevel_Num5x5;
	}

	return 1;
}

void SaveManager::SetLastUnlockedLevel(int num)
{
	if(_saveData->GameID == NUM_3x3)
	{
		if(num <= _saveData->TotalLevels_Num3x3+1)
		{
			_saveData->LastUnlockedLevel_Num3x3 = num;
		}
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		if(num <= _saveData->TotalLevels_Num4x4+1)
			_saveData->LastUnlockedLevel_Num4x4 = num;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		if(num <= _saveData->TotalLevels_Num5x5+1)
			_saveData->LastUnlockedLevel_Num5x5 = num;
	}
}

int SaveManager::GetLastUnlockedLevel()
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->LastUnlockedLevel_Num3x3;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->LastUnlockedLevel_Num4x4;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->LastUnlockedLevel_Num5x5;
	}

	return 1;
}

int SaveManager::GetTotalLevelsPlayed()
{
	return GetLastUnlockedLevel()-1;
}

void SaveManager::SetNumStars(int numStars, int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		_saveData->NumStarsArray_Num3x3[levelNum-1] = numStars;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		_saveData->NumStarsArray_Num4x4[levelNum-1] = numStars;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		_saveData->NumStarsArray_Num5x5[levelNum-1] = numStars;
	}
}

int SaveManager::GetNumStars(int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->NumStarsArray_Num3x3[levelNum-1];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->NumStarsArray_Num4x4[levelNum-1];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->NumStarsArray_Num5x5[levelNum-1];
	}

	return 0;
}

void SaveManager::SetNumMoves(int numMoves, int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		_saveData->NumMovesArray_Num3x3[levelNum-1] = numMoves;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		_saveData->NumMovesArray_Num4x4[levelNum-1] = numMoves;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		_saveData->NumMovesArray_Num5x5[levelNum-1] = numMoves;
	}
}

int SaveManager::GetNumMoves(int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->NumMovesArray_Num3x3[levelNum-1];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->NumMovesArray_Num4x4[levelNum-1];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->NumMovesArray_Num5x5[levelNum-1];
	}

	return 0;
}

void SaveManager::SetTime(int seconds, int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		_saveData->TimeArray_Num3x3[levelNum-1] = seconds;
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		_saveData->TimeArray_Num4x4[levelNum-1] = seconds;
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		_saveData->TimeArray_Num5x5[levelNum-1] = seconds;
	}
}

int SaveManager::GetTime(int levelNum)
{
	if(_saveData->GameID == NUM_3x3)
	{
		return _saveData->TimeArray_Num3x3[levelNum-1];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		return _saveData->TimeArray_Num4x4[levelNum-1];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		return _saveData->TimeArray_Num5x5[levelNum-1];
	}

	return 0;
}

int SaveManager::GetTotalStars()
{
	int sum = 0;

	if(_saveData->GameID == NUM_3x3)
	{
		for(int i=0; i<_saveData->TotalLevels_Num3x3; i++)
			sum += _saveData->NumStarsArray_Num3x3[i];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		for(int i=0; i<_saveData->TotalLevels_Num4x4; i++)
			sum += _saveData->NumStarsArray_Num4x4[i];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		for(int i=0; i<_saveData->TotalLevels_Num5x5; i++)
			sum += _saveData->NumStarsArray_Num5x5[i];
	}

	return sum;
}

int SaveManager::GetTotalTime()
{
	int sum = 0;

	if(_saveData->GameID == NUM_3x3)
	{
		for(int i=0; i<_saveData->TotalLevels_Num3x3; i++)
			sum += _saveData->TimeArray_Num3x3[i];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		for(int i=0; i<_saveData->TotalLevels_Num4x4; i++)
			sum += _saveData->TimeArray_Num4x4[i];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		for(int i=0; i<_saveData->TotalLevels_Num5x5; i++)
			sum += _saveData->TimeArray_Num5x5[i];
	}

	return sum;
}

int SaveManager::GetTotalMoves()
{
	int sum = 0;

	if(_saveData->GameID == NUM_3x3)
	{
		for(int i=0; i<_saveData->TotalLevels_Num3x3; i++)
			sum += _saveData->NumMovesArray_Num3x3[i];
	}
	else if(_saveData->GameID == NUM_4x4)
	{
		for(int i=0; i<_saveData->TotalLevels_Num4x4; i++)
			sum += _saveData->NumMovesArray_Num4x4[i];
	}
	else if(_saveData->GameID == NUM_5x5)
	{
		for(int i=0; i<_saveData->TotalLevels_Num5x5; i++)
			sum += _saveData->NumMovesArray_Num5x5[i];
	}

	return sum;
}

SaveManager::~SaveManager()
{
	if(_saveData)
	{
		delete _saveData;
		_saveData = NULL;
	}
}

void SaveManager::DeleteInstance()
{
	if(_ref)
	{
		delete _ref;
		_ref = NULL;
	}
}
