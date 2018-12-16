#ifdef _PLATFORM_WIN32

#ifndef PLATFORM_WIN32_H
#define PLATFORM_WIN32_H

#include "Platform.h"
#include "GameLoop.h"
#include "MusicPlayer.h"
#include <string>

class Platform_Win32 : public Platform
{
private:
	std::string _saveFolderPath;
	std::string _dataFolderPath;

	GameLoop* _gameLoop;
	MusicPlayer* _musicPlayer;

public:

	Platform_Win32();
	~Platform_Win32();

	// Implementation of Platform pure virtual functions...
	void onCreate();
	void onSizeChange(int width, int height);
	int Draw(int deltaTimeInMillis);
	void onTouch(int x, int y, int eventID);
	void onPause();
	void onResume();
	void onExit();

	void SetSaveFolderPath(std::string saveFolderPath);
	void SetDataFolderPath(std::string dataFolderPath);

	string GetSaveFolderPath();
	string GetDataFolderPath();

	
	char* GetFileData(std::string filePath, int* fileMemSize, int readFrom);
	bool SetSaveData(void* data, unsigned int size);
	bool GetSaveData(void* data, unsigned int size);

	void PlayMusic(bool play);
	bool IsMusicPlaying();
	float GetTimeInSeconds();
	int GetTimeInMillis();

	void ShowMsg(char* str);
	void SetBackKeyPressed();
};

#endif


#endif
