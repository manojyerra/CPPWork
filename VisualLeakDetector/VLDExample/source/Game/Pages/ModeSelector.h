#ifndef MODESELECTOR_H
#define MODESELECTOR_H
#pragma once

#include "ButtonNew.h"
#include "Page.h"

class ModeSelector : Page
{
private:
	ButtonNew* _playBtn3;
	ButtonNew* _playBtn4;
	ButtonNew* _playBtn5;
	ButtonNew* _homeBtn;

public:
	ModeSelector();
	~ModeSelector();
	void Update();
	void Draw();
};

#endif
