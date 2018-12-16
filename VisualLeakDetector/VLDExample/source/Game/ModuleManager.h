#ifndef MODULE_H
#define MODULE_H
#pragma once

#include "Logos.h"
#include "PagesManager.h"
#include "NumberPuzzleMain4x4.h"

class ModuleManager
{
private:
	static ModuleManager* _ref;
	ModuleManager();
	~ModuleManager();

	int _currModule;
	int _nextModule;

	Logos* _logos;
	PagesManager* _pagesManager;
	NumberPuzzleMain4x4* _numberPuzzle4x4;

public:
	static const int NONE = 0;
	static const int LOGOS = 1;
	static const int PAGES = 2;
	static const int GAME = 3;

	static ModuleManager* GetInstance();
	static void DeleteInstance();

	void* GetModuleObject(int moduleID);

	void Update();
	void SetModule(int module);
	int GetModule();
	void CheckModuleChange();
	void Draw();
};


#endif
