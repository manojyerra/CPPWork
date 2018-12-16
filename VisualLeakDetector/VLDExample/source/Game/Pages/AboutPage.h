#ifndef MORE_GAMES_H
#define MORE_GAMES_H
#pragma once

#include "RectPrim.h"
#include "Button.h"

#include "Page.h"

class MoreGames : public Page
{
private:
	RectPrim* _bg;
	Button* _backBtn;
	Button* _game1Btn;

public:
	MoreGames();
	~MoreGames();
	void Update();
	void Draw();

	bool IsGame1Clicked();
};

#endif