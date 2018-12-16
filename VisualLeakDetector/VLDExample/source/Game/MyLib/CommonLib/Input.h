#pragma once

#include <vector>


class TouchInput
{
public:
	int x;
	int y;
	bool leftMouseDown;

	TouchInput(int x, int y, bool leftMouseDown)
	{
		this->x = x;
		this->y = y;
		this->leftMouseDown = leftMouseDown;
	}
};

class Input
{
private:
	static int StoreX;
	static int StoreY;

	static bool STORE_LEFT_MOUSE_DOWN;

	static bool LEFT_MOUSE_DOWN;
	static bool PREV_LEFT_MOUSE_DOWN;

	static std::vector<TouchInput> touchVec;

	static float timeBetweenClickAndRelease;

	static bool StoreBackKeyPressed;
	static bool BackKeyPressed;

public:
	static int MouseX;
	static int MouseY;

	static int PrevMouseX;
	static int PrevMouseY;

	static int MouseClickX;
	static int MouseClickY;

	static int MouseReleaseX;
	static int MouseReleaseY;



	static void Update();

	static void onTouch(int x, int y, int eventID);

	static bool IsMouseClicked();
	static bool IsMousePressed();
	static bool IsMouseReleased();
	static bool IsBackPressed();
	static void SetBackKeyPressed();

	static float GetDistBetweenClickAndRelease();
	static float GetTimeBetweenClickAndRelease();
	static int GetDirection();
};
