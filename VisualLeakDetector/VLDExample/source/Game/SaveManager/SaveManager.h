#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#pragma once

#include "SaveData.h"

class SaveManager
{
	SaveData* _saveData;
	static SaveManager* _ref;
	SaveManager();
	~SaveManager();

public:
	static const int NUM_3x3 = 1;
	static const int NUM_4x4 = 2;
	static const int NUM_5x5 = 3;

	static SaveManager* GetInstance();
	static void DeleteInstance();

	SaveData* GetSaveData();
	void SaveGame();

	void SetGameID(int gameID);
	int GetGameID();
	
	void FillDefaultValues();
	void ReadSave();

	int GetNumTotalLevels();

	void SetLastUnlockedLevel(int num);
	int GetLastUnlockedLevel();
	int GetTotalLevelsPlayed();

	void SetCurrLevel(int levelNum);
	int GetCurrLevel();

	void SetNumStars(int numStars, int levelNum);
	int GetNumStars(int levelNum);

	void SetNumMoves(int numMoves, int levelNum);
	int GetNumMoves(int levelNum);

	void SetTime(int seconds, int levelNum);
	int GetTime(int levelNum);

	int GetTotalStars();
	int GetTotalTime();
	int GetTotalMoves();

	void Terminate();
};
#endif
