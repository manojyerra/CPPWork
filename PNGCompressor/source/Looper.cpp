#include "Looper.h"
#include "Input.h"
#include "math.h"
#include "DefinesAndIncludes.h"
#include "ImageBuffer.h"

void shift_left(unsigned char *ar, int size, int leftShift)
{
	if(size <= 0)
		return;

	unsigned char carry = 0;

	ar[0] <<= leftShift;

	int rightShift = 8-leftShift;

	for(int i=1; i<size; i++)
	{
		carry = ar[i] >> rightShift;
		ar[i] <<= leftShift;
		ar[i-1] |= carry;
	}
}


Looper::Looper(int windowWidth, int windowHeight)
{
	unsigned int intVal  = 0x00ffbbff;
	unsigned int intVal2 = 0x00ffbbff;

	

	unsigned int intValShift2 = intVal << 1;

	unsigned char charArr[4];

	charArr[0] = 0x00;
	charArr[1] = 0xff;
	charArr[2] = 0xbb;
	charArr[3] = 0xff;

	unsigned int intBackBeforeShift = (unsigned int)((charArr[0]<<24) + (charArr[1]<<16) + (charArr[2]<<8) + charArr[3]);

	shift_left(charArr, 4, 1);

	unsigned int intBack = (unsigned int)((charArr[0]<<24) + (charArr[1]<<16) + (charArr[2]<<8) + charArr[3]);

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
