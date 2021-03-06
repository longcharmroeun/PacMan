// PacMan.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PacMan.h"
#include "Graphic.h"
#include "SpriteSheet.h"
#include "Property.h"
#include "Food1.h"
#include "Food.h"


#define MAX_LOADSTRING 100

Graphic *graphics = new Graphic;
Food1 food1;
Food food;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

bool Down = false;
bool Up = false;
bool Left = false;
bool Right = false;
int check_food = 0;

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
	int Score = 0;
	int Level = 1;
	int mimilliseconds = 0;
	


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
		if ((Message.message == WM_KEYDOWN && Message.wParam == 'W')||(Message.message == WM_KEYDOWN && Message.wParam == VK_UP)) {
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
		if ((Message.message == WM_KEYDOWN && Message.wParam == 'A')||(Message.message == WM_KEYDOWN && Message.wParam == VK_LEFT)) {
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
		if ((Message.message == WM_KEYDOWN && Message.wParam == 'D')||(Message.message == WM_KEYDOWN && Message.wParam == VK_RIGHT)) {
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

		
			if (!(x < 850 - 10 - 20)) {
				if (Right) Right = false;
			}
			if (!(x > 20 + 20)) {
				if (Left) Left = false;
			}
			if (y < 100 + 10 + 20) {
				if (Up) Up = false;
			}
			if (y > 580 - 20 - 10) {
				if (Down) Down = false;
			}
			if (Down) y += YSPEED;
			else if (Up) y -= YSPEED;
			else if (Left) x -= XSPEED;
			else if (Right) x += XSPEED;
			graphics->BeginDraw();
			graphics->ClearScreen(0, 0, 0);
			graphics->DrawCircle(SIZE_PLAYER ,x, y, 20, 250, 0, 0);
			graphics->DrawRectangle(SIZE_WALL ,10, 100, 850, 580, 0, 200, 0);

			graphics->DrawRectangle(SIZE_WALL, 38 + 30, 128 + 30, 800 / 2, 128 + 100, 0, 200, 0);
			graphics->DrawRectangle(SIZE_WALL, 800 / 2 + 65, 128 + 30, 800 - 10, 128 + 100, 0, 200, 0);

			graphics->DrawRectangle(SIZE_WALL, 38 + 30, 128 + 30 + 140, 800 / 2, 128 + 100 + 140, 0, 200, 0);
			graphics->DrawRectangle(SIZE_WALL, 800 / 2 + 65, 128 + 30 + 140, 800 - 10, 128 + 100 + 140, 0, 200, 0);

			graphics->DrawRectangle(SIZE_WALL, 38 + 30, 128 + 30 + 140 + 140, 800 / 2, 128 + 100 + 140 + 140, 0, 200, 0);
			graphics->DrawRectangle(SIZE_WALL, 800 / 2 + 65, 128 + 30 + 140 + 140, 800 - 10, 128 + 100 + 140 + 140, 0, 200, 0);

			int foodx = 38;
			int foody = 128;
			int foodx1 = 38;
			int foody1 = 190;
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					if (x > foodx1 - 15 && x<foodx1 + 15 && y>foody1 - 15 && y < foody1 + 15) {
						if (!(food1.IsEated(i, j))) {
							food1.Eat(i, j);
						}
					}
					if (food1.IsEat(i,j)) {
						Score += FOODSCORE;
						food1.Eated(i, j);
						check_food++;
					}
					if(!(food1.IsEated(i,j))) {
						graphics->DrawCircle(SIZE_FOOD, foodx1, foody1, 1, 1, 1, 1);
					}
					foodx1 += 393;
				}
				foodx1 = 38;
				foody1 += 140;
			}

			for (size_t i = 0; i < 4; i++)
			{
				for (size_t j = 0; j < 20; j++)
				{
					if (x > foodx - 15 && x<foodx + 15 && y>foody - 15 && y < foody + 15) {
						if (!(food.IsEated(i, j))) {
							food.Eat(i, j);
						}
					}
					if (food.IsEat(i, j)) {
						Score += FOODSCORE;
						food.Eated(i, j);
						check_food++;
					}
					if(!(food.IsEated(i,j))) {
						graphics->DrawCircle(SIZE_FOOD, foodx, foody, 1, 1, 1, 1);
					}
					foodx += 60;
				}
				foody += 140;
				foodx = 38;
			}

			if (check_food >= 65) {
				food.~Food();
				food1.~Food1();
				check_food = 0;
				if(Right) Right= false;
				if (Down == true) Down = false;
				if (Up == true) Up = false;
				if (Left == true) Left = false;
				y = 128;
				x = 38;
				Level++;
			}

			mimilliseconds++;
			if (mimilliseconds >= 20) {
				graphics->DrawText(L"PacMan", 40, 340, 10, 550, 40, 50, 50, 0);
				graphics->DrawText(L"Level", 30, 340, 10, 520, 100, 50, 25, 25);
				wsprintf(text, TEXT("%d"), Level);
				graphics->DrawText(text, 30, 340, 10, 600, 100, 50, 25, 25);
			}
			if (mimilliseconds >= 40) mimilliseconds = 0;

			wsprintf(text, TEXT("%d"),Score);
			graphics->DrawText(TEXT("Score"), 40, 10, 10, 100, 40, 25, 0, 25);
			graphics->DrawText(text, 40, 50, 10, 250, 40, 25, 0, 25);

			graphics->EndDraw();
			wsprintf(text, TEXT("%d,%d"), x, y);
			SetWindowText(Dialog, text);
			
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
