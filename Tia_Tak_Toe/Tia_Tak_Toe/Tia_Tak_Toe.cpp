// Tia_Tak_Toe.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Tia_Tak_Toe.h"
#include <windowsx.h>
#include "Enemy.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
Enemy enemy;
WNDPROC StaticWndProc = NULL;
BOOL Easy = true;
BOOL Hard = false;
BOOL Checked = true;
// Forward declarations of functions included in this code module:

BOOL CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	MSG msg;
	HWND Dialog = CreateDialog(hInst, MAKEINTRESOURCE(IDD_BOX), NULL, WndProc);
	ShowWindow(Dialog, nCmdShow);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

int mx, my;
RECT r{ 200,100,500,100 * 4 };
static int win = 0, lose = 0, draw = 0;
TCHAR text[100];
HWND Check;
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
			case IDC_EASY:
				if (Hard) {
					Check = GetDlgItem(hWnd, IDC_HARD);
					SendMessage(Check, BM_SETCHECK, BST_UNCHECKED, 0);
					enemy.~Enemy();
					InvalidateRect(hWnd, &r, true);
					lose = win = draw = 0;
					wsprintf(text, TEXT("%d"), draw);
					HWND hDraw = GetDlgItem(hWnd, IDC_DRAW);
					SetWindowText(hDraw, text);
					wsprintf(text, TEXT("%d"), win);
					HWND hWin = GetDlgItem(hWnd, IDC_WIN);
					SetWindowText(hWin, text);
					wsprintf(text, TEXT("%d"), lose);
					HWND hLose = GetDlgItem(hWnd, IDC_LOSE);
					SetWindowText(hLose, text);
				}
				Check = GetDlgItem(hWnd, IDC_HARD);
				Hard = SendMessage(Check, BM_GETCHECK, BST_CHECKED, 0);
				Check = GetDlgItem(hWnd, IDC_EASY);
				Easy = SendMessage(Check, BM_GETCHECK, BST_CHECKED, 0);
				break;
			case IDC_HARD:
				if (Easy) {
					Check = GetDlgItem(hWnd, IDC_EASY);
					SendMessage(Check, BM_SETCHECK, BST_UNCHECKED, 0);
					enemy.~Enemy();
					InvalidateRect(hWnd, &r, true);
					lose = win = draw = 0;
					wsprintf(text, TEXT("%d"), draw);
					HWND hDraw = GetDlgItem(hWnd, IDC_DRAW);
					SetWindowText(hDraw, text);
					wsprintf(text, TEXT("%d"), win);
					HWND hWin = GetDlgItem(hWnd, IDC_WIN);
					SetWindowText(hWin, text);
					wsprintf(text, TEXT("%d"), lose);
					HWND hLose = GetDlgItem(hWnd, IDC_LOSE);
					SetWindowText(hLose, text);
				}
				Check = GetDlgItem(hWnd, IDC_HARD);
				Hard = SendMessage(Check, BM_GETCHECK, BST_CHECKED, 0);
				Check = GetDlgItem(hWnd, IDC_EASY);
				Easy = SendMessage(Check, BM_GETCHECK, BST_CHECKED, 0);
				break;
			case IDB_RESTART:
			{
				enemy.~Enemy();
				InvalidateRect(hWnd, &r, true);
				lose = win = draw = 0;
				wsprintf(text, TEXT("%d"), draw);
				HWND hDraw = GetDlgItem(hWnd, IDC_DRAW);
				SetWindowText(hDraw, text);
				wsprintf(text, TEXT("%d"), win);
				HWND hWin = GetDlgItem(hWnd, IDC_WIN);
				SetWindowText(hWin, text);
				wsprintf(text, TEXT("%d"), lose);
				HWND hLose = GetDlgItem(hWnd, IDC_LOSE);
				SetWindowText(hLose, text);
			}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
		if (Checked) {
			Check = GetDlgItem(hWnd, IDC_EASY);
			SendMessage(Check, BM_SETCHECK, BST_CHECKED, 0);
			Checked = false;
		}
		    int x = 200, y = 100;
            PAINTSTRUCT ps;
			HPEN hpen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
            HDC hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, hpen);
			for (size_t i = 0; i < enemy.Getsize(); i++)
			{
				for (size_t j = 0; j < enemy.Getsize(); j++)
				{
					if (enemy.Getbox(i,j) == 0) {
						Rectangle(hdc, x, y, x + 100, y + 100);
						HPEN Mehpen = CreatePen(PS_SOLID, 10, RGB(10, 255, 0));
						SelectObject(hdc, Mehpen);
						Ellipse(hdc, x+10, y+10, x+100-11, y + 100-11);
						SelectObject(hdc, hpen);
					}
					else if (enemy.Getbox(i, j) == 1) {
						Rectangle(hdc, x, y, x + 100, y + 100);
						HPEN Enemyhpen = CreatePen(PS_SOLID, 10, RGB(10, 0, 0));
						SelectObject(hdc, Enemyhpen);
						MoveToEx(hdc, x + 15, y + 15, NULL);
						LineTo(hdc, x + 100 - 15, y + 100 - 15);
						MoveToEx(hdc, x + 15, y + 100 - 15, NULL);
						LineTo(hdc, x + 100 - 15, y + 15);
						SelectObject(hdc, hpen);
					}
					else Rectangle(hdc, x, y, x + 100, y + 100);
					x = x + 100;
				}
				y = y + 100;
				x = 200;
			}

            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		int x = 200, y = 100;
		mx = GET_X_LPARAM(lParam);
		my = GET_Y_LPARAM(lParam);
		for (size_t i = 0; i < enemy.Getsize(); i++)
		{
			for (size_t j = 0; j < enemy.Getsize(); j++)
			{
				if (mx >= x && mx <= x + 100 && my >= y && my <= y + 100) {
					if (enemy.IsEmpty(i,j)) {
						enemy.Isme(i, j);
						InvalidateRect(hWnd, &r, true);
						enemy.outtext(hWnd);
						if (enemy.Check() == 2) {
							MessageBox(hWnd, TEXT("Win"), TEXT("Tia Tak Toe"), MB_OK | MB_ICONINFORMATION);
							enemy.~Enemy();
							InvalidateRect(hWnd, &r, true);
							win++;
							wsprintf(text, TEXT("%d"), win);
							HWND hWin = GetDlgItem(hWnd, IDC_WIN);
							SetWindowText(hWin, text);
						}
						if (Easy) enemy.Easy();
						else enemy.Hard();
						InvalidateRect(hWnd, &r, true);
						if (enemy.Check() == 3) {
							MessageBox(hWnd, TEXT("Lose"), TEXT("Tia Tak Toe"), MB_OK | MB_ICONINFORMATION);
							enemy.~Enemy();
							InvalidateRect(hWnd, &r, true);
							lose++;
							wsprintf(text, TEXT("%d"), lose);
							HWND hWin = GetDlgItem(hWnd, IDC_LOSE);
							SetWindowText(hWin, text);

						}
						if (enemy.Check() == 4) {
							MessageBox(hWnd, TEXT("Draw"), TEXT("Tia Tak Toe"), MB_OK | MB_ICONINFORMATION);
							enemy.~Enemy();
							InvalidateRect(hWnd, &r, true);
							draw++;
							wsprintf(text, TEXT("%d"), draw);
							HWND hWin = GetDlgItem(hWnd, IDC_DRAW);
							SetWindowText(hWin, text);
						}
					}
				}
				x = x + 100;
			}
			y = y + 100;
			x = 200;
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
