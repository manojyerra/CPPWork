#ifndef OPTIONS_H
#define OPTIONS_H
#pragma once

#include "CommonLib/Sprite.h"
#include "CommonLib/Input.h"
#include "CommonLib/Button.h"

#include "Page.h"
#include <vector>
using namespace std;

class Options : Page
{
private:
	Sprite* _bg;
	Button* _backBtn;
	//Button* _creditsBtn;

	Sprite* _sfxImg;
	Sprite* _bgmImg;

	Sprite* _sfxBarImg;
	Sprite* _musicBarImg;

	Sprite* _sfxPointerImg;
	Sprite* _musicPointerImg;

	bool _sfxActive;
	bool _bgmActive;

	int _sfxVolume;
	int _bgmVolume;
	int _gapX;

	bool _clickedOnSfxBtn;
	bool _clickedOnMusicBtn;

public:
	Options();
	~Options();
	void Init();
	void Update();
	void UpdateSFXBar();
	void UpdateBGMBar();
	void Draw();
};

#endif
