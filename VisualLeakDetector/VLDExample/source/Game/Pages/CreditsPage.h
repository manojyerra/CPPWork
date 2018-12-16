#ifndef CREDITS_PAGE_H
#define CREDITS_PAGE_H
#pragma once

#include "Page.h"
#include "CommonLib/Sprite.h"
#include "CommonLib/Button.h"

class CreditsPage : public Page
{
private:
	Sprite* _bg;
	Button* _backBtn;

public:
	CreditsPage();
	~CreditsPage();
	void Update();
	void Draw();
};

#endif