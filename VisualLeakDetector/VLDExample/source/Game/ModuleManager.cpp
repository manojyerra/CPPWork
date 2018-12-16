#include "ModuleManager.h"
#include "SaveManager.h"

ModuleManager* ModuleManager::_ref = NULL;

ModuleManager::ModuleManager()
{
	_logos = NULL;
	_pagesManager = NULL;
	_numberPuzzle4x4 = NULL;

	_currModule = NONE;
	_nextModule = _currModule;

	_pagesManager = PagesManager::GetInstance();
	_pagesManager->Init();

	SetModule(PAGES);
	CheckModuleChange();
}

ModuleManager* ModuleManager::GetInstance()
{
	if(_ref == NULL)
		_ref = new ModuleManager();
	return _ref;
}

void ModuleManager::SetModule(int module)
{
	_nextModule = module;

	if(_nextModule == _currModule && _nextModule == GAME)
	{
		if(_numberPuzzle4x4)
		{
			delete _numberPuzzle4x4;
			_numberPuzzle4x4 = NULL;
		}
		if(_numberPuzzle4x4 == NULL)
		{
			_numberPuzzle4x4 = new NumberPuzzleMain4x4();
		}
	}
}

int ModuleManager::GetModule()
{
	return _currModule;
}

void* ModuleManager::GetModuleObject(int moduleID)
{
	if(moduleID == LOGOS)
	{
		return _logos;
	}
	else if(moduleID == PAGES)
	{
		return _pagesManager;
	}
	else if(moduleID == GAME)
	{
		return _numberPuzzle4x4;
	}
	
	return NULL;
}

void ModuleManager::Update()
{
	CheckModuleChange();

	if(_currModule == LOGOS)
	{
		if(_logos)
		{
			_logos->Update();
			if(_logos->HasShownLogos())
				SetModule(PAGES);
		}
	}
	else
	if(_currModule == PAGES)
	{
		if(_pagesManager)
			_pagesManager->Update();
	}
	else if(_currModule == GAME)
	{
		if(_numberPuzzle4x4)
			_numberPuzzle4x4->Update();
	}
}


void ModuleManager::CheckModuleChange()
{
	if(_nextModule != _currModule)
	{
		//Deleting current module....
		if(_currModule == LOGOS)
		{
			if(_logos)
			{
				delete _logos;
				_logos = NULL;
			}
		}
		else
		if(_currModule == GAME)
		{
			if(_numberPuzzle4x4)
			{
				delete _numberPuzzle4x4;
				_numberPuzzle4x4 = NULL;
			}
		}

		//Loading Next Module here.....
		if(_nextModule == LOGOS)
		{
			if(_logos == NULL)
			{
				_logos = new Logos();
			}
		}
		else 
		if(_nextModule == PAGES)
		{
			if(_pagesManager == NULL)
			{
				_pagesManager = PagesManager::GetInstance();
				_pagesManager->Init();
			}
		}
		else if(_nextModule == GAME)
		{
			if(_numberPuzzle4x4 == NULL)
			{
				_numberPuzzle4x4 = new NumberPuzzleMain4x4();
			}
		}

		_currModule = _nextModule;
	}
}

void ModuleManager::Draw()
{
	if(_currModule == LOGOS)
	{
		if(_logos)
			_logos->Draw();
	}
	else 
	if(_currModule == PAGES)
	{
		if(_pagesManager)
			_pagesManager->Draw();
	}
	else if(_currModule == GAME)
	{
		if(_numberPuzzle4x4)
			_numberPuzzle4x4->Draw();
	}
}

ModuleManager::~ModuleManager()
{
	if(_logos)
	{
		delete _logos;
		_logos = NULL;
	}

	if(_pagesManager)
	{
		PagesManager::DeleteInstance();
		_pagesManager = NULL;
	}

	if(_numberPuzzle4x4)
	{
		delete _numberPuzzle4x4;
		_numberPuzzle4x4 = NULL;
	}
}

void ModuleManager::DeleteInstance()
{
	if(_ref)
	{
		delete _ref;
		_ref = NULL;
	}
}