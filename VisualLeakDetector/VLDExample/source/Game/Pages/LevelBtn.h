#ifndef LEVEL_BTN_H
#define LEVEL_BTN_H
#pragma once

#include "Sprite.h"
#include "Button.h"
#include "ButtonNew.h"

class LevelBtn
{
private:
	ButtonNew* _btn;
	int _number;

	Sprite* _disableStars[3];
	Sprite* _enableStars[3];


public:

	LevelBtn(ButtonNew* btn, int number);
	~LevelBtn();

	void Update();
	void SetBounds(int x, int y, int w, int h);
	bool IsClicked();
	void SetEnable(bool enable);
	bool IsEnabled();
	void Move(int x, int y);
	int GetNumber();
	void Draw();
};

#endif
