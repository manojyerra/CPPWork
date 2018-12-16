#ifndef LOGOS_H
#define LOGOS_H
#pragma once

#include "CommonLib/Sprite.h"
#include <vector>
using namespace std;

class Logos
{
private:
	static const int NUM_LOGOS = 4;

	vector<Sprite*> _spriteVec;
	vector<float> _timeVec;

	int _currLogoIndex;
	float _timeCount;
	bool _shownLogos;
	int _transSpeed;

public:
	Logos();
	void Update();
	bool HasShownLogos();
	void Move(float dx, float dy);
	void Draw();
	~Logos();
};
#endif