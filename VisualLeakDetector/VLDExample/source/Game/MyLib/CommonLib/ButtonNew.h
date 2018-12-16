#ifndef BUTTONNEW_H
#define BUTTONNEW_H

#include "TextureInfo.h"
#include <string>
using namespace std;

class ButtonNew
{
private:
	float _x;
	float _y;
	float _w;
	float _h;

	int c1[4];
	int c2[4];

	string _text;
	float _fontSizePercent;
	bool _isClicked;
	int _colorID;
	bool _isEnable;
	TextureInfo* _borderTex;

	bool _addBump;

	void DrawRect(int x, int y, int w, int h, int r1, int g1, int b1, int a1, int r2, int g2, int b2, int a2);
	void DrawRoundedBorder(int x, int y, int w, int h);
	void DrawRoundedRect(int x, int y, int w, int h, float u, float v, float cw, float ch);


public:
	static const int COLOR1 = 1;
	static const int COLOR2 = 2;
	static const int COLOR3 = 3;
	static const int COLOR4 = 4;
	static const int COLOR5 = 5;
	static const int COLOR_EMPTY = 6;
	static const int COLOR_DISABLE = 7;

	ButtonNew(string text, float x, float y, float w, float h, int colorID);
	~ButtonNew();

	string GetName();
	void SetName(string text);
	void SetFontSizeInPercent(float fontSizePercent);

	void Update();
	bool Contains(float x, float y);
	bool IsClicked();	
	void Draw();

	void SetAddBump(bool addBump);

	void SetColorID(int colorID);
	void SetColor(int r, int g, int b, int a);
	void SetTopColor(int r, int g, int b, int a);
	void SetBottomColor(int r, int g, int b, int a);

	void SetEnable(bool enable);
	bool IsEnabled();

	void SetBounds(float x, float y, float w, float h);
	void SetX(float x);
	void SetY(float y);
	void SetPos(float x, float y);
	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
};

#endif
