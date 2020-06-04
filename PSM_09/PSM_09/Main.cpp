#include <Windows.h>
#include "mainwin.h"
#include <iostream>

#pragma warning (disable : 4996)

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"\"Cellular automata\" move window to see the UI", WS_OVERLAPPEDWINDOW,hInstance,nCmdShow))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	MSG msg = {};

	using namespace std;

	SYSTEMTIME time;

	GetSystemTime(&time);

	int timePassed = time.wMinute*60000 + time.wSecond*1000 + time.wMilliseconds;

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		GetSystemTime(&time);
		if (time.wMinute * 60000 + time.wSecond * 1000 + time.wMilliseconds - timePassed > 500)
		{
			timePassed = time.wMinute * 60000 + time.wSecond * 1000 + time.wMilliseconds;
			win.Update();
		}

	}
	return 0;
}