#include "Input.h"
#include "math.h"
#include "Includes.h"
#include "GameInfo.h"
#include "Dir.h"

int Input::StoreX = 0;
int Input::StoreY = 0;

int Input::MouseX = 0;
int Input::MouseY = 0;

int Input::PrevMouseX = 0;
int Input::PrevMouseY = 0;

int Input::MouseClickX = 0;
int Input::MouseClickY = 0;

int Input::MouseReleaseX = 0;
int Input::MouseReleaseY = 0;

bool Input::LEFT_MOUSE_DOWN = false;
bool Input::PREV_LEFT_MOUSE_DOWN = false;
bool Input::STORE_LEFT_MOUSE_DOWN = false;

bool Input::StoreBackKeyPressed = false;
bool Input::BackKeyPressed = false;

float Input::timeBetweenClickAndRelease = 0;

std::vector<TouchInput> Input::touchVec;

void Input::Update()
{
	if(touchVec.size() > 0)
	{
		StoreX = touchVec[0].x;
		StoreY = touchVec[0].y;
		STORE_LEFT_MOUSE_DOWN = touchVec[0].leftMouseDown;

		touchVec.erase(touchVec.begin()+0);
	}

	BackKeyPressed = false;

	PrevMouseX = MouseX;
	PrevMouseY = MouseY;

	GameInfo* in = GameInfo::GetInstance();

	MouseX = (StoreX - in->drawX) * in->CodedW() / in->drawW;
	MouseY = (StoreY - in->drawY) * in->CodedW() / in->drawW;

	PREV_LEFT_MOUSE_DOWN = LEFT_MOUSE_DOWN;
	LEFT_MOUSE_DOWN = STORE_LEFT_MOUSE_DOWN;

	if(IsMouseClicked())
	{
		PrevMouseX = MouseX;
		PrevMouseY = MouseY;

		MouseClickX = MouseX;
	    MouseClickY = MouseY;

		timeBetweenClickAndRelease = 0;
	}
	else if(IsMouseReleased())
	{
		MouseReleaseX = MouseX;
		MouseReleaseY = MouseY;
	}

	if(IsMousePressed())
		timeBetweenClickAndRelease += GameInfo::deltaTime;

	BackKeyPressed = StoreBackKeyPressed;
	StoreBackKeyPressed = false;
}

void Input::onTouch(int x, int y, int eventID)
{
	if(eventID == 1)
	{
		touchVec.push_back(TouchInput(x,y,true));
	}
	else if(eventID == 2)
	{
		touchVec.push_back(TouchInput(x,y,false));
	}

	//printLog("touchVec size : %d", touchVec.size());
}

bool Input::IsMouseClicked() { return (LEFT_MOUSE_DOWN && !PREV_LEFT_MOUSE_DOWN); }
bool Input::IsMousePressed() { return (LEFT_MOUSE_DOWN); }
bool Input::IsMouseReleased(){ return (!LEFT_MOUSE_DOWN && PREV_LEFT_MOUSE_DOWN); }

bool Input::IsBackPressed()
{
	return BackKeyPressed;
}

void Input::SetBackKeyPressed()
{
	StoreBackKeyPressed = true;
}

float Input::GetDistBetweenClickAndRelease()
{
	float dx = (MouseClickX - MouseReleaseX);
	float dy = (MouseClickY - MouseReleaseY);

	return sqrt( dx*dx + dy*dy);
}

int Input::GetDirection()
{
	float RAD_DEG = 57.295780f;

	float dx = (MouseReleaseX - MouseClickX);
	float dy = (MouseReleaseY - MouseClickY);

	float angle = atan2( dy, dx) * RAD_DEG;

	if(angle < 0)
		angle += 360;

	if(angle > 45 && angle <= 135)
		return Dir::DOWN;
	else if(angle > 135 && angle <= 225)
		return Dir::LEFT;
	else if(angle > 225 && angle <= 315)
		return Dir::UP;

	return Dir::RIGHT;
}

float Input::GetTimeBetweenClickAndRelease()
{
	return timeBetweenClickAndRelease;
}