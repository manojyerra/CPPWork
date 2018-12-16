#ifdef _PLATFORM_WIN32

#include "vld.h"
#include <stdlib.h>
#include "Platform.h"
#include "Includes.h"
#include "Win32Window.h"

#define WIN_SCREEN_W 1024
#define WIN_SCREEN_H 600

//#define WIN_SCREEN_W 480*0.5
//#define WIN_SCREEN_H 858*0.5

Win32Window* win32Window = NULL;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	win32Window = new Win32Window();
	win32Window->CreateWin32Window(hInstance, "classFirst", 0,0,WIN_SCREEN_W,WIN_SCREEN_H);

	Platform::GetPlatform()->onCreate();
	Platform::GetPlatform()->onSizeChange(WIN_SCREEN_W, WIN_SCREEN_H);
	Platform::GetPlatform()->SetDataFolderPath("../../assets");
	Platform::GetPlatform()->SetSaveFolderPath("./");

	bool prevLeftMouseDown = win32Window->LEFT_MOUSE_DOWN;
	int startTime = GetTickCount();

	bool isActive = true;

	while(!win32Window->DeviceCheckQuitRequest())
	{
		win32Window->DeviceYield(20);

		if(prevLeftMouseDown != win32Window->LEFT_MOUSE_DOWN || win32Window->LEFT_MOUSE_DOWN)
		{
			POINT pos;
			GetCursorPos(&pos);

			if(win32Window->LEFT_MOUSE_DOWN)
				Platform::GetPlatform()->onTouch(pos.x-9, pos.y-30, 1);
			else
				Platform::GetPlatform()->onTouch(pos.x-9, pos.y-30, 2);
		}

		prevLeftMouseDown = win32Window->LEFT_MOUSE_DOWN;

		int deltaTimeInMillis = (int)(GetTickCount() - startTime);
    	startTime = GetTickCount();

		if(isActive != Win32Window::isActive)
		{
			isActive = Win32Window::isActive;
			if(isActive)
				Platform::GetPlatform()->onResume();
			else
				Platform::GetPlatform()->onPause();
		}

		Platform::GetPlatform()->Draw(deltaTimeInMillis);
		win32Window->Swap_Buffers();
	}

	Platform::GetPlatform()->onExit();
	Platform::GetPlatform()->DeletePlatform();

	if(win32Window)
	{
		delete win32Window;
		win32Window = NULL;
	}

	return 0;
}

#endif
