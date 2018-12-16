#ifndef INCLUDES_H
#define INCLUDES_H


#ifdef _PLATFORM_ANDROID

#include <android/log.h>
#include <GLES/gl.h>

#define printLog(...)	__android_log_print(ANDROID_LOG_INFO,"CPPNDK",__VA_ARGS__)

#endif




#ifdef _PLATFORM_WIN32

#include <windows.h>
#include <gl/gl.h>
#include "stdio.h"

#define GL_CLAMP_TO_EDGE GL_CLAMP
#define glOrthof glOrtho

#define printLog Includes::print

class Includes
{
public:
	static void print(const char * pszFormat, ...)
	{
		const int MAX_LEN = 10000;
		char szBuf[MAX_LEN];

		va_list ap;
		va_start(ap, pszFormat);
		vsnprintf_s(szBuf, MAX_LEN, MAX_LEN, pszFormat, ap);
		va_end(ap);

		WCHAR wszBuf[MAX_LEN] = {0};
		MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, wszBuf, sizeof(wszBuf));
		OutputDebugStringW(wszBuf);
		OutputDebugStringA("\n");

		//WideCharToMultiByte(CP_ACP, 0, wszBuf, sizeof(wszBuf), szBuf, sizeof(szBuf), NULL, FALSE);
		//printf("%s\n", szBuf);
	}
};

#endif



#endif //INCLUES_H
