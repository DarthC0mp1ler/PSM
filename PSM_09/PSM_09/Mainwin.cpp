#include "mainwin.h"
#include <iostream>


using namespace D2D1;
#pragma warning(disable : 4996)


HRESULT MainWindow::CreateGraphicsResourcses()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		RECT rc;
		GetClientRect(clientRect, &rc);

		D2D1_SIZE_U size = SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			RenderTargetProperties(),
			HwndRenderTargetProperties(clientRect, size),
			&pRenderTarget
		);

		if (SUCCEEDED(hr))
		{
			const D2D1_COLOR_F color = ColorF(0.f, 1.0f, 0.f);
			hr = pRenderTarget->CreateSolidColorBrush(color, &pBrushCell);
			const D2D1_COLOR_F color1 = ColorF(1.0f, 1.0f, 1.0f);
			hr = pRenderTarget->CreateSolidColorBrush(color1, &pBrushBorder);
			const D2D1_COLOR_F color2 = ColorF(1.0f, 0.0f, 0.f);
			hr = pRenderTarget->CreateSolidColorBrush(color2, &pBrushEmptyCell);

			if (FAILED(hr))  PostQuitMessage(0);
		}
	}
	return hr;
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	SafeRelease(&pBrushCell);
	SafeRelease(&pBrushBorder);
	SafeRelease(&pBrushEmptyCell);
}

void MainWindow::OnPaint()
{
	HRESULT hr = CreateGraphicsResourcses();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(clientRect, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(ColorF(ColorF::LightSkyBlue));

		if (BoardCreated)
		{
			pBoard->PaintCells({ pRenderTarget,pBrushCell,pBrushEmptyCell,pBrushBorder });
		}

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}

		EndPaint(clientRect, &ps);
	}
}


void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		RECT rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		RECT rc;
		GetClientRect(m_hwnd, &rc);
		clientRect = CreateWindow(L"static", L"",
			WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			220, 0, rc.right, rc.bottom,
			m_hwnd, NULL,
			NULL, NULL);
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
		{
			return -1;
		}
		CreateUi();
	case WM_COMMAND:
		switch (wParam)
		{
		case 1:
			if (!BoardCreated) {
				wchar_t arr[19];
				GetWindowText(ruleField, arr, 19);
				pBoard = new Board(arr);
				BoardCreated = true;
			}
			else
			{
				wchar_t arr[19];
				GetWindowText(ruleField, arr, 19);
				pBoard->UpdateRules(arr);
			}
			break;
		case 2:
			std::cout << "start  = "<< stop << std::endl;
			stop = !stop;
			break;
		}
	
		return 0;

	case WM_MOUSEMOVE:
		if (!buttonDown || mouseMsgCount < 15) {
			if (buttonDown)
				mouseMsgCount++;
			break;
		}
		mouseMsgCount = 0;
	case WM_LBUTTONDOWN: {

		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);
		float x = static_cast<float>(xPos) / scaleX - 220,
			y = static_cast<float>(yPos) / scaleY;
		pBoard->ChangeCell(x, y);
		InvalidateRect(m_hwnd, NULL, FALSE);
		buttonDown = true;
	}
					   break;
	case WM_LBUTTONUP:
		buttonDown = false;
		break;
	case WM_DESTROY:
		delete(pBoard);
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		OnPaint();
		return 0;
	case WM_SIZE:
		Resize();
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}

void MainWindow::Update()
{
	if (BoardCreated && !stop) {
		pBoard->Step();
	}
}


void MainWindow::CreateUi()
{
	ruleLabel = CreateWindow(L"static", L"Rules:",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		10, 10, 50, 25,
		m_hwnd, NULL,
		NULL, NULL);

	ruleField = CreateWindow(L"edit", L"23/3",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		60, 10, 150, 25,
		m_hwnd, NULL,
		NULL, NULL);
	changeRules = CreateWindow(
		L"BUTTON",
		L"New Rules",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 35, 100, 30,
		m_hwnd,
		(HMENU)1, NULL, NULL);

	CreateWindow(
		L"BUTTON",
		L"Start",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
		10, 65, 100, 30,
		m_hwnd,
		(HMENU)2, NULL, NULL);

	UpdateWindow(m_hwnd);
}