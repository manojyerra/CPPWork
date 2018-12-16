#ifndef POS_H
#define POS_H
#pragma once

class Pos
{
public:
	float x;
	float y;

	Pos(){}
	Pos(float xPos, float yPos)
	{
		x = xPos;
		y = yPos;
	}

	//inline bool operator == (const Pos &p2)	
	//{
	//	return (x == p2.x && y == p2.y);
	//}
};

#endif