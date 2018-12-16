#include"PauseScreen.h"
#include "PagesManager.h"
#include "Options.h"
#include "ModuleManager.h"
#include "GameInfo.h"
#include "Platform.h"
#include "ColorTheme.h"

PauseScreen::PauseScreen()
{
	_resume = new ButtonNew("Back",0,0,218*0.655,87*0.625,ButtonNew::COLOR_EMPTY);
	_isActive = false;
	_isMusicPlayingBeforePause = false;
}

void PauseScreen::Update()
{
	_resume->Update();

	if(_resume->IsClicked())
		SetActive(false);
}

void PauseScreen::SetActive(bool isActive)
{
	_isActive = isActive;

	if(_isActive)
	{
		_isMusicPlayingBeforePause = Platform::GetPlatform()->IsMusicPlaying();
		Platform::GetPlatform()->PlayMusic( false );
	}
	else
		Platform::GetPlatform()->PlayMusic(_isMusicPlayingBeforePause);
}

bool PauseScreen::IsActive()
{
	return _isActive; 
}

void PauseScreen::Draw()
{
	ColorTheme::Draw();

	_resume->Draw();
}

PauseScreen::~PauseScreen()
{
	if(_resume)
	{
		delete _resume;
		_resume = NULL;
	}
}







