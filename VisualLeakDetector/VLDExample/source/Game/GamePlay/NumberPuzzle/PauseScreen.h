#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H
#pragma once

#include "ButtonNew.h"

class PauseScreen
{
private:
	ButtonNew* _resume;
	bool _isActive;
	bool _isMusicPlayingBeforePause;

public:

	PauseScreen();
	~PauseScreen();
	void Update();
	void Draw();
	void SetActive(bool isActive);
	bool IsActive();
};
#endif