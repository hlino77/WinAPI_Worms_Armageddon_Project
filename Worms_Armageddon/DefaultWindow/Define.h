#pragma once

#define			WINCX		1600
#define			WINCY		900

#define			MAPPOSX		1310
#define			MAPPOSY		780

#define			PURE		= 0

#define			VK_MAX			0xff


#define			PI			3.141592f

#define RAD2DEG(rad) (rad * (180 / PI))
#define DEG2RAD(deg) (deg * (PI / 180))

#include <iostream>
using namespace std;

//
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif

typedef struct tagInfo
{
	float	fX;
	float	fY;
	float	fCX;
	float	fCY;

}INFO;


extern HWND	g_hWnd;

extern float g_fVolume;