#ifndef Looper_H
#define Looper_H


#include "SUI/SUI.h"
#include "SUI/SUIInput.h"
#include "SUI/SUIActionListener.h"

#include "UIFrames/MainFrame.h"

class Looper
{
private:
	float _windowW;
	float _windowH;
	MainFrame* _mainFrame;

public:
	Looper(int windowWidth, int windowHeight);
	~Looper();

	void Draw(float deltaTime);
};

#endif
