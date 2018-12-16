#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Button.h"
#include "GameInit.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "ButtonNew.h"

class GameLoop
{
private:
	int _textureID;
	bool _init;
	bool _onResume;

	GameInit* _gameInit;
	Button* _sfxBtn;
	Button* _bgmBtn;

	bool _isMusicPlayingBeforePause;

	ButtonNew* _btnNew;
	Sprite* _tempSprite;

	float GetVal(vector<float> numVec, vector<int> symbolID);
	float GetVal(string str);
	void PrintSolutions(vector<float> numVec, int result);
	char ch(int id);

	void GradientDemo();
	void DrawRect(int x, int y, int w, int h, int r1, int g1, int b1, int r2, int g2, int b2);
	void DrawRoundedRect(int x, int y, int w, int h, float u1, float v1, float u2, float v2);
	void DrawRoundedBorder(int x, int y, int w, int h);

public:
	GameLoop();
	~GameLoop();
	void Init();

	void onCreate();
	void onSizeChange(int surfaceW, int surfaceH);
	void Update(int deltaTimeInMillis);
	int Draw(int deltaTimeInMillis);
	void onTouch(int x, int y, int eventID);
	void onPause();
	void onResume();

	void SetLanguageID(int languageID);
	void SetBackKeyPressed();

	unsigned int GenerateGLTextureID(unsigned char* buffer, int width, int height, int bytesPerPixel);
	void DrawTexture(int textureID, int x, int y, int w, int h);
};

#endif
