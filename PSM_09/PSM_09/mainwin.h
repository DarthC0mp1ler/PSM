#include <windows.h>
#include <d2d1.h>
#include <WindowsX.h>
#pragma comment(lib,"d2d1")

#include "basewin.h"
#include "boardbase.h"

#ifndef __MAINWIN_H_
#define __MAINWIN_H_

template <class T>
void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class MainWindow : public BaseWindow<MainWindow>
{
	float scaleX = 1.;
	float scaleY = 1.;

	HWND clientRect;

	bool buttonDown = false;
	int mouseMsgCount = 0;

	Board* pBoard;
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrushCell;
	ID2D1SolidColorBrush* pBrushEmptyCell;
	ID2D1SolidColorBrush* pBrushBorder;
	HWND ruleLabel;
	HWND changeRules;
	
	bool BoardCreated = false;
	bool stop = true;

public:
	HWND ruleField;
private:

	HRESULT CreateGraphicsResourcses();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();
	void CreateUi();

	

public:
	MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrushCell(NULL),pBrushBorder(NULL),pBrushEmptyCell(NULL) {}

	PCWSTR ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Update();
};

#endif

