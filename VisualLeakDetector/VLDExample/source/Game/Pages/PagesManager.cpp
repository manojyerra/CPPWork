#include "PagesManager.h"

PagesManager* PagesManager::_ref = NULL;

PagesManager::PagesManager()
{
}

PagesManager* PagesManager::GetInstance()
{
	if(_ref == NULL)
		_ref = new PagesManager();
	return _ref;
}

void PagesManager::Init()
{
	_currPage = NULL;
	_mainMenu = NULL;
	_options = NULL;
	_credits = NULL;
	_levelSelector = NULL;
	_moreGames = NULL;
	_modeSelector = NULL;
	_modeSelectorForLB = NULL;

	_pagesVec.clear();

	_mainMenu = new MainMenu(); 
	_pagesVec.push_back((Page*)_mainMenu);

	_modeSelector = new ModeSelector(); 
	_pagesVec.push_back((Page*)_modeSelector);

	_modeSelectorForLB = new ModeSelectorForLB(); 
	_pagesVec.push_back((Page*)_modeSelectorForLB);

	_options = new Options(); 
	_pagesVec.push_back((Page*)_options);

	_credits = new CreditsPage(); 
	_pagesVec.push_back((Page*)_credits);

	_levelSelector = new LevelSelector();
	_pagesVec.push_back((Page*)_levelSelector);

	//_moreGames = new MoreGames();
	//_pagesVec.push_back((Page*)_moreGames);

	_currPage = (Page*)_mainMenu;
	_nextPage = (Page*)_mainMenu;;
}

void PagesManager::Update()
{
	if(_nextPage != _currPage)
		_currPage = _nextPage;

	if(_currPage)
		_currPage->Update();
}

Page* PagesManager::GetPage(int currPageID)
{
	if(currPageID == MAINMENU)						return (Page*)_mainMenu;
	else if(currPageID == MODE_SELECTOR)			return (Page*)_modeSelector;
	else if(currPageID == MODE_SELECTOR_FOR_LB)		return (Page*)_modeSelectorForLB;
	else if(currPageID == OPTIONS)					return (Page*)_options;
	else if(currPageID == MORE_GAMES)				return (Page*)_moreGames;
	else if(currPageID == LEVEL_SELECTOR)			return (Page*)_levelSelector;

	return NULL;
}

void PagesManager::SetCurrPage(int currPageID)
{
	if(currPageID == MAINMENU)						_nextPage = (Page*)_mainMenu;
	else if(currPageID == MODE_SELECTOR)			_nextPage = (Page*)_modeSelector;
	else if(currPageID == MODE_SELECTOR_FOR_LB)		_nextPage = (Page*)_modeSelectorForLB;
	else if(currPageID == OPTIONS)					_nextPage = (Page*)_options;
	else if(currPageID == MORE_GAMES)				_nextPage = (Page*)_moreGames;
	else if(currPageID == LEVEL_SELECTOR)			_nextPage = (Page*)_levelSelector;
	else											_nextPage = NULL;
}

int PagesManager::GetCurrPageID()
{
	if(_currPage == (Page*)_mainMenu)					return MAINMENU;
	else if(_currPage == (Page*)_modeSelector)			return MODE_SELECTOR;
	else if(_currPage == (Page*)_modeSelectorForLB)		return MODE_SELECTOR_FOR_LB;
	else if(_currPage == (Page*)_options)				return OPTIONS;
	else if(_currPage == (Page*)_moreGames)				return MORE_GAMES;
	else if(_currPage == (Page*)_levelSelector)			return LEVEL_SELECTOR;

	return -1;
}

void PagesManager::Draw()
{
	if(_currPage)
		_currPage->Draw();
}

PagesManager::~PagesManager()
{
	for(int i=0;i<_pagesVec.size();i++)
	{
		if(_pagesVec[i])
		{
			delete _pagesVec[i];
			_pagesVec[i] = NULL;
		}
	}
	_pagesVec.clear();
}


void PagesManager::DeleteInstance()
{
	if(_ref)
	{
		delete _ref;
		_ref = NULL;
	}
}