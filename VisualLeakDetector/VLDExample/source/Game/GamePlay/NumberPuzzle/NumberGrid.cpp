#include "NumberGrid.h"
#include "SaveManager.h"
#include "UIFont.h"
#include "CirclePrim.h"
#include "RectPrim.h"

NumberGrid::NumberGrid(int number, float x, float y, float drawWidth, float drawHeight, int levelNum)
{
	_number = number;
	sprintf(_numStr, "%d", number);

	_x = x;
	_y = y;
	_w = drawWidth;
	_h = drawHeight;

	_initX = _x;
	_initY = _y;

	_statusImgW = 25;

	_rightImg = new Sprite("right.png", _x+_w-2*_statusImgW, _y+_statusImgW, _statusImgW, _statusImgW);

	char pathArr[256];
	sprintf(pathArr, "fly/%d.jpg", levelNum);

	_numberImg = new Sprite(pathArr, _x, _y, _w, _h);

	float u = 0;
	float v = 0;
	float cw = 0;
	float ch = 0;

	int gameMode = SaveManager::GetInstance()->GetGameID();

	if(gameMode == SaveManager::NUM_3x3)
	{
		cw = 1.0f/3.0f;
		ch = 1.0f/3.0f;
		u = ((number-1)%3) * cw;
		v = ((number-1)/3) * ch;
	}
	else if(gameMode == SaveManager::NUM_4x4)
	{
		cw = 1.0f/4.0f;
		ch = 1.0f/4.0f;
		u = ((number-1)%4) * cw;
		v = ((number-1)/4) * ch;
	}
	else if(gameMode == SaveManager::NUM_5x5)
	{
		cw = 1.0f/5.0f;
		ch = 1.0f/5.0f;
		u = ((number-1)%5) * cw;
		v = ((number-1)/5) * ch;
	}

	_numberImg->SetUVBounds0To1(u, v, cw, ch);

	_isMoving = false;
	_justNowMoveOver = false;
	_direction = NONE;
	_speed = 30;
	_destin = -1;
	_glow = false;
}

void NumberGrid::Update(float deltaTime)
{
}

void NumberGrid::Move(int direction)
{
}

bool NumberGrid::MoveOverJustNow()
{
	return _justNowMoveOver;
}

void NumberGrid::Glow(bool glow)
{
	_glow = glow;
}

bool NumberGrid::IsMoving()
{
	return _isMoving;
}

bool NumberGrid::Contains(float x, float y)
{
	return (x >= _x && x <= _x+_w && y >= _y && y <= _y+_h);
}

float NumberGrid::GetX(){ return _x; }
float NumberGrid::GetY(){ return _y; }
float NumberGrid::GetW(){ return _w; }
float NumberGrid::GetH(){ return _h; }

void NumberGrid::SetX(float x)
{
	SetBounds(x, _y, _w, _h);
}

void NumberGrid::SetY(float y)
{
	SetBounds(_x, y, _w, _h);
}

void NumberGrid::SetBounds(float x, float y, float w, float h)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;

	_numberImg->SetBounds(_x,_y,_w,_h);

	_rightImg->SetBounds(_x+_w-2*_statusImgW, _y+2*_statusImgW, _statusImgW, _statusImgW);
	_rightImg->SetVisible( ((int)_initX == (int)_x && (int)_initY == (int)_y) );
}

void NumberGrid::Draw()
{
	_numberImg->Draw();
	RectPrim::DrawBorder(_x, _y, _w, _h, 1, 0x00000077);
	_rightImg->Draw();
}
	
NumberGrid::~NumberGrid()
{
	if(_numberImg)
	{
		delete _numberImg;
		_numberImg = NULL;
	}
}
