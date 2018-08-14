// PacMan.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PacMan.h"
#include "Graphic.h"
#include "SpriteSheet.h"

#define MAX_LOADSTRING 100

Graphic *graphics = new Graphic;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

bool Down = false;
bool Up = false;
bool Left = false;
bool Right = false;
TCHAR text[100];

// Forward declarations of functions included in this code module:
//ATOM                MyRegisterClass(HINSTANCE hInstance);
//BOOL                InitInstance(HINSTANCE, int);
BOOL CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	HWND Dialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PACMAN), NULL, (DLGPROC)WndProc);
	if (!graphics->Init(Dialog)) {
		delete graphics;
		return -1;
	}
	ShowWindow(Dialog, nCmdShow);
	MSG Message;
	int y = 128;
	int x = 38;
	Message.message = WM_NULL;
	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) DispatchMessage(&Message);
		if ((Message.message == WM_KEYDOWN && Message.wParam == 'S')||(Message.message == WM_KEYDOWN && Message.wParam == VK_DOWN)) {
			if (x > 38 + 30 - 30 && x < 800 / 2 + 30) {
				if (Down) Down = false;
			}
			else if (x > 800 / 2 + 65 - 30 && x < 800 - 10 + 30) {
				if (Down) Down = false;
			}
			else {
				Down = true;
				if (Up == true) Up = false;
				if (Left == true) Left = false;
				if (Right == true) Right = false;
			}
		}
		else if ((Message.message == WM_KEYDOWN && Message.wParam == 'W')||(Message.message == WM_KEYDOWN && Message.wParam == VK_UP)) {
			if (x > 38 + 30 - 30 && x < 800 / 2 + 30) {
				if (Up) Up = false;
			}
			else if (x > 800 / 2 + 65 - 30 && x < 800 - 10 + 30) {
				if (Up) Up = false;
			}
			else {
				Up = true;
				if (Down == true) Down = false;
				if (Left == true) Left = false;
				if (Right == true) Right = false;
			}
		}
		else if ((Message.message == WM_KEYDOWN && Message.wParam == 'A')||(Message.message == WM_KEYDOWN && Message.wParam == VK_LEFT)) {
			if (y > 128 + 30 - 30 && y < 128 + 100 + 30) {
				if (Left) Left = false;
			}
			else if (y > 128 + 30 + 140 - 30 && y < 128 + 100 + 140 + 30) {
				if (Left) Left = false;
			}
			else if (y > 128 + 30 + 140 + 140 - 30 && y < 128 + 100 + 140 + 140 + 30) {
				if (Left) Left = false;
			}
			else {
				Left = true;
				if (Down == true) Down = false;
				if (Up == true) Up = false;
				if (Right == true) Right = false;
			}
		}
		else if ((Message.message == WM_KEYDOWN && Message.wParam == 'D')||(Message.message == WM_KEYDOWN && Message.wParam == VK_RIGHT)) {
			if (y > 128 + 30 - 30 && y < 128 + 100 + 30) {
				if (Right) Right = false;
			}
			else if (y > 128 + 30 + 140 - 30 && y < 128 + 100 + 140 + 30) {
				if (Right) Right = false;
			}
			else if (y > 128 + 30 + 140 + 140 - 30 && y < 128 + 100 + 140 + 140 + 30) {
				if (Right) Right = false;
			}
			else {
				Right = true;
				if (Down == true) Down = false;
				if (Up == true) Up = false;
				if (Left == true) Left = false;
			}
		}
		else {
			if (!(x < 850 - 10 - 20)) {
				if (Right) Right = false;
			}
			if (!(x > 20 + 20)) {
				if (Left) Left = false;
			}
			if (y < 100 + 10 + 20) {
				if (Up) Up = false;
			}
			if (y > 600 - 20 - 10) {
				if (Down) Down = false;
			}


			if (Down) y += 5;
			else if (Up) y -= 5;
			else if (Left) x -= 5;
			else if (Right) x += 5;
			graphics->BeginDraw();
			graphics->ClearScreen(0, 0, 0);
			graphics->DrawCircle(x, y, 20, 250, 0, 0);
			graphics->DrawRectangle(10, 100, 850, 600, 0, 200, 0);

			graphics->DrawRectangle(38 + 30, 128 + 30, 800/2, 128+100, 0, 200, 0);
			graphics->DrawRectangle(800/2 + 65, 128 + 30, 800 - 10 , 128 + 100, 0, 200, 0);

			graphics->DrawRectangle(38 + 30, 128 + 30+140, 800 / 2, 128 + 100+140, 0, 200, 0);
			graphics->DrawRectangle(800 / 2 + 65, 128 + 30+140, 800 - 10, 128 + 100+140, 0, 200, 0);

			graphics->DrawRectangle(38 + 30, 128 + 30 + 140 + 140, 800 / 2, 128 + 100 + 140 + 140, 0, 200, 0);
			graphics->DrawRectangle(800 / 2 + 65, 128 + 30 + 140 + 140, 800 - 10, 128 + 100 + 140 + 140, 0, 200, 0);

			graphics->EndDraw();
			wsprintf(text, TEXT("%d,%d"), x, y);
			SetWindowText(Dialog, text);
			if (x > 38 + 30 - 30 && x < 800 / 2 + 30 && y > 128 + 30 - 30 && y < 128 + 100 + 30) {
				SetWindowText(Dialog, TEXT("HELOO"));
			}
			//RECT rect;
			//GetClientRect(Dialog, &rect);
			//wsprintf(text, TEXT("%d,%d"), rect.bottom, rect.right);
			//SetWindowText(Dialog, text);
		}
	}
	delete graphics;
	return Message.wParam;
}


BOOL CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return TRUE;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return false;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
