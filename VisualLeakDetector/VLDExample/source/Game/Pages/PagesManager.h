#ifndef PAGESMANAGER_H
#define PAGESMANAGER_H
#pragma once

#include "Input.h"
#include "MainMenu.h"
#include "ModeSelector.h"
#include "ModeSelectorForLB.h"
#include "Options.h"
#include "LevelSelector.h"
#include "CreditsPage.h"
#include "AboutPage.h"

#include "Page.h"
#include <vector>
using namespace std;

class PagesManager
{
private:
	static PagesManager* _ref;

	Page* _currPage;
	Page* _nextPage;
	
	MainMenu* _mainMenu;
	ModeSelector* _modeSelector;
	ModeSelectorForLB* _modeSelectorForLB;
	Options* _options;
	CreditsPage* _credits;
	LevelSelector* _levelSelector;
	MoreGames* _moreGames;

	PagesManager();
	~PagesManager();

public:
	vector<Page*> _pagesVec;

	static const int NONE					= 0;
	static const int MAINMENU				= 1;
	static const int MODE_SELECTOR			= 2;
	static const int MODE_SELECTOR_FOR_LB	= 3;
	static const int CONTINUE				= 4;
	static const int OPTIONS				= 5;
	static const int LEVEL_SELECTOR			= 6;
	static const int MORE_GAMES				= 7;


	static PagesManager* GetInstance();
	static void DeleteInstance();

	void Init();
	void Update();
	void Draw();
	
	Page* GetPage(int currPageID);
	void SetCurrPage(int currPageID);
	int GetCurrPageID();
};

#endif
