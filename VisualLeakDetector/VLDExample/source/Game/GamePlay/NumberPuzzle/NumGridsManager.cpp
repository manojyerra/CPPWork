#include "NumGridsManager.h"
#include "Input.h"
#include "GameInfo.h"
#include "Dir.h"
#include "SaveManager.h"

NumGridsManager::NumGridsManager(int numXGrids, int* arr)
{
	_numXGrids = numXGrids;
	_totGrids = (_numXGrids*_numXGrids);

	int levelNum = SaveManager::GetInstance()->GetCurrLevel();

	char pathArr[256];
	sprintf(pathArr, "fly/%d.jpg", levelNum);
	_finalImg = new Sprite(pathArr, 0,0,0,0);
	TextureInfo* texInfo = _finalImg->GetTextureInfo();
	_finalImg->SetSize(texInfo->width, texInfo->height);

	float screenW = GameInfo::GetInstance()->CodedW();
	float screenH = GameInfo::GetInstance()->CodedH();

	float btnW = 115;
	float remaingW = screenW - btnW;
	float remaingH = screenH;

	if(_finalImg->GetWidth() > remaingW)
	{
		_finalImg->SetHeight(_finalImg->GetHeight() * remaingW / _finalImg->GetWidth());
		_finalImg->SetWidth(remaingW);
	}

	if(_finalImg->GetHeight() > remaingH)
	{
		_finalImg->SetWidth(_finalImg->GetWidth() * remaingH / _finalImg->GetHeight());
		_finalImg->SetHeight(remaingH);
	}

	_initX = btnW + (remaingW - _finalImg->GetWidth()) / 2;
	_initY = (remaingH - _finalImg->GetHeight()) / 2;

	_finalImg->SetPos(_initX, _initY);

	_drawWidth = _finalImg->GetWidth() / _numXGrids;
	_drawHeight = _finalImg->GetHeight() / _numXGrids;
	_numbersVec.clear();

	int count = 0;

	for(int row=0; row<_numXGrids; row++)
	{
		for(int col=0; col<_numXGrids; col++)
		{
			int x = _initX + col*_drawWidth;
			int y = _initY + row*_drawHeight;

			count++;

			NumberGrid* numberGrid = new NumberGrid(count, x,y,_drawWidth,_drawHeight, levelNum);
			_numbersVec.push_back(numberGrid);

			if(count >= _totGrids)
				break;
		}

		if(count >= _totGrids)
			break;
	}

	count = 0;
	for(int row=0;row<_numXGrids;row++)
	{
		for(int col=0;col<_numXGrids;col++)
		{
			int x = _initX + col*_drawWidth;
			int y = _initY + row*_drawHeight;

			int index = arr[count]-1;
			if(index < _numbersVec.size())
				_numbersVec[index]->SetBounds(x,y,_drawWidth,_drawHeight);

			count++;
			if(count >= _totGrids)
				break;
		}

		if(count >= _totGrids)
			break;
	}

	_borderX = _initX;
	_borderY = _initY;
	_borderW = _drawWidth*_numXGrids;
	_borderH = _drawHeight*_numXGrids;

	_glowAllGrids = false;
	_showFinalImg = false;
}

int NumGridsManager::GetGridIndex(NumberGrid* grid)
{
	for(int i=0; i<_numbersVec.size(); i++)
	{
		if(grid == _numbersVec[i])
			return i;
	}
	return -1;
}

NumberGrid* NumGridsManager::GetGrid(float x, float y)
{
	for(int i=0; i<_numbersVec.size(); i++)
	{
		if(_numbersVec[i]->Contains(x,y))
			return _numbersVec[i];
	}
	return NULL;
}

NumberGrid* NumGridsManager::GetGridByIndex(int index)
{
	if(index < _numbersVec.size())
		return _numbersVec[index];

	return NULL;
}

bool NumGridsManager::IsWithInBorder(float x, float y)
{
	return ( x >= _borderX &&  x <= _borderX+_borderW && y >= _borderY &&  y <= _borderY+_borderH );
}

bool NumGridsManager::CanMove(NumberGrid* numberGrid, int dir)
{
	float midX = numberGrid->GetX() + numberGrid->GetW()/2;
	float midY = numberGrid->GetY() + numberGrid->GetH()/2;

	float x = 0;
	float y = 0;

	if(dir == Dir::RIGHT)
	{
		x = midX + numberGrid->GetW();
		y = midY;
		if(IsWithInBorder(x,y) && !GetGrid(x,y))
			return true;
	}
	else if(dir == Dir::LEFT)
	{
		x = midX - numberGrid->GetW();
		y = midY;
		if(IsWithInBorder(x,y) && !GetGrid(x,y))
			return true;
	}
	else if(dir == Dir::DOWN)
	{
		x = midX;
		y = midY + numberGrid->GetH();
		if(IsWithInBorder(x,y) && !GetGrid(x,y))
			return true;
	}
	else if(dir == Dir::UP)
	{
		x = midX;
		y = midY - numberGrid->GetH();
		if(IsWithInBorder(x,y) && !GetGrid(x,y))
			return true;
	}

	return false;
}

int NumGridsManager::GetEmptySpaceDirection(NumberGrid* numberGrid)
{
	float midX = numberGrid->GetX() + numberGrid->GetW()/2;
	float midY = numberGrid->GetY() + numberGrid->GetH()/2;

	float x = 0;
	float y = 0;

	//right
	x = midX + numberGrid->GetW();
	y = midY;
	if(IsWithInBorder(x,y) && !GetGrid(x,y))
		return NumberGrid::RIGHT;

	//left
	x = midX - numberGrid->GetW();
	y = midY;
	if(IsWithInBorder(x,y) && !GetGrid(x,y))
		return NumberGrid::LEFT;

	//down
	x = midX;
	y = midY + numberGrid->GetH();
	if(IsWithInBorder(x,y) && !GetGrid(x,y))
		return NumberGrid::DOWN;

	//up
	x = midX;
	y = midY - numberGrid->GetH();
	if(IsWithInBorder(x,y) && !GetGrid(x,y))
		return NumberGrid::UP;

	return NumberGrid::NONE;
}

bool NumGridsManager::IsInCorrectOrder()
{
	int count = 0;
	for(int row=0;row<_numXGrids;row++)
	{
		for(int col=0;col<_numXGrids;col++)
		{
			int x = _initX + col*_drawWidth +  _drawWidth/2.0f;
			int y = _initY + row*_drawHeight + _drawHeight/2.0f;

			if(!_numbersVec[count]->Contains(x, y))
				return false;

			count++;
			if(count >= _totGrids)
				break;
		}
		if(count >= _totGrids)
			break;
	}

	return true;
}

bool NumGridsManager::IsAnyGridMoveFinishedJustNow()
{
	for(int i=0; i<_numbersVec.size(); i++)
		if(_numbersVec[i]->MoveOverJustNow())
			return true;

	return false;
}

NumberGrid* NumGridsManager::GetIntersectGrid(NumberGrid* numGrid)
{
	NumberGrid* grid = NULL;

	float minDist = 0;

	float hw = numGrid->GetW()/2;
	float hh = numGrid->GetH()/2;

	float mx = numGrid->GetX() + hw;
	float my = numGrid->GetY() + hh;

	for(int i=0; i<_numbersVec.size(); i++)
	{	
		if(_numbersVec[i] != numGrid)
		{
			if(_numbersVec[i]->Contains(mx, my))
			{
				if(grid == NULL)
				{
					grid = _numbersVec[i];

					float nmx = grid->GetX() + grid->GetW()/2;
					float nmy = grid->GetY() + grid->GetH()/2;

					minDist = (nmx-mx) * (nmx-mx) + (nmy-my)*(nmy-my);
				}
				else
				{
					float nmx = _numbersVec[i]->GetX() + _numbersVec[i]->GetW()/2;
					float nmy = _numbersVec[i]->GetY() + _numbersVec[i]->GetH()/2;

					float dist = (nmx-mx) * (nmx-mx) + (nmy-my)*(nmy-my);

					if(dist < minDist)
					{
						minDist = dist;
						grid = _numbersVec[i];
					}
				}
			}
		}
	}

	return grid;
}

void NumGridsManager::Update(float deltaTime)
{
	for(int i=0; i<_numbersVec.size(); i++)
		_numbersVec[i]->Update(deltaTime);

	/*
	if(Input::IsMouseReleased())
	{
		int moveDir = Input::GetDirection();

		bool moved = false;

		do
		{
			moved = false;

			for(int i=0; i<_numbersVec.size(); i++)
			{
				if(CanMove(_numbersVec[i], moveDir))
				{
					_numbersVec[i]->Move(moveDir);
					_numbersVec[i]->Update(deltaTime);
					moved = true;
				}
			}
		}
		while(moved);
	}
	*/
}

bool NumGridsManager::IsAnyGridMoving()
{
	for(int i=0; i<_numbersVec.size(); i++)
		if(_numbersVec[i]->IsMoving())
			return true;

	return false;
}

void NumGridsManager::Glow(bool glow)
{
	_glowAllGrids = glow;

	//for(int i=0; i<_numbersVec.size(); i++)
	//	_numbersVec[i]->Glow(glow);
}

bool NumGridsManager::IsAllGridsGlowing()
{
	return _glowAllGrids;
}

void NumGridsManager::ShowFinalImg(bool showFinalImg)
{
	_showFinalImg = showFinalImg;
}

void NumGridsManager::Draw(NumberGrid* numGrid)
{
	if(_glowAllGrids || _showFinalImg)
	{
		_finalImg->Draw();
	}
	else
	{
		for(int i=0; i<_numbersVec.size(); i++)
		{
			if(numGrid != _numbersVec[i])
				_numbersVec[i]->Draw();
		}

		if(numGrid)
			numGrid->Draw();
	}
}

NumGridsManager::~NumGridsManager()
{
	for(int i=0; i<_numbersVec.size(); i++)
	{
		if(_numbersVec[i])
		{
			delete _numbersVec[i];
			_numbersVec[i] = NULL;
		}
	}
	_numbersVec.clear();


	if(_finalImg)
	{
		delete _finalImg;
		_finalImg = NULL;
	}
}
