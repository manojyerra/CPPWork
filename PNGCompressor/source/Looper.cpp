#include "Looper.h"
#include "Input.h"
#include "math.h"
#include "DefinesAndIncludes.h"
#include "ImageBuffer.h"

Looper::Looper(int windowWidth, int windowHeight)
{
	_windowW = (float)windowWidth;
	_windowH = (float)windowHeight;

	SUISetup((int)_windowW, (int)_windowH);

	_mainFrame = new MainFrame(0,0,_windowW,_windowH);

	//_mainFrame->SetMaximize( true );
}

void Looper::Draw(float deltaTime)
{
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	SUIInput::Update((float)Input::MX, (float)Input::MY, Input::LEFT_BUTTON_DOWN, deltaTime);

	SUIDraw();
}

Looper::~Looper()
{
	SUIQuit();
}
