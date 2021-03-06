// TimerProject.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TimerProject.h"
#include <ctime>
#include <cmath>
#define MAX_LOADSTRING 100
#define M_PI 3.1415
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / M_PI)


// Global Variables:
HWND hh, hmin, hsec;
time_t t;
struct tm *local;
TCHAR text[100];

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Menu(HWND hwnd) {
	hh = CreateWindowEx(0, TEXT("STATIC"), TEXT("12"), WS_CHILD | WS_BORDER | WS_VISIBLE, 100, 30, 20, 20, hwnd, NULL, hInst, NULL);
	CreateWindowEx(0, TEXT("STATIC"), TEXT(":"), WS_CHILD  | WS_VISIBLE, 125, 30, 10, 20, hwnd, NULL, hInst, NULL);
	hmin = CreateWindowEx(0, TEXT("STATIC"), TEXT("00"), WS_CHILD | WS_BORDER | WS_VISIBLE, 140, 30, 20, 20, hwnd, NULL, hInst, NULL);
	CreateWindowEx(0, TEXT("STATIC"), TEXT(":"), WS_CHILD | WS_VISIBLE, 165, 30, 10, 20, hwnd, NULL, hInst, NULL);
	hsec = CreateWindowEx(0, TEXT("STATIC"), TEXT("00"), WS_CHILD | WS_BORDER | WS_VISIBLE, 180, 30, 20, 20, hwnd, NULL, hInst, NULL);
}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TIMERPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMERPROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIMERPROJECT));
    wcex.hCursor        = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_POINTER));
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TIMERPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
  // Menu(hWnd);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
int midX, midY, r, clockSize;
TCHAR wcs[100];
PAINTSTRUCT ps;
HDC hdc;
RECT *rect = new RECT;
PSIZE tsize = new SIZE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int tid = 1, counter = 0, counter1 = 0, counter2 = 0;
	double angle = 90 - ((360.0 / 60)*counter);
	double angleMIN = 90 - ((360.0 / 60)*counter1);
	double angleH = 90 - ((360.0 / 60)*counter2);

    switch (message)
    {
	case WM_CREATE:
		Menu(hWnd);
		SetTimer(hWnd, tid, 1000, NULL);
		break;
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
			case ID_START:
				t = time(NULL);
				local = localtime(&t);
				wsprintf(text, TEXT("%d"), local->tm_sec);
				counter = _ttoi(text);
				SetWindowText(hsec, text);
				wsprintf(text, TEXT("%d"), local->tm_min);
				counter1 = _ttoi(text);
				SetWindowText(hmin, text);
				wsprintf(text, TEXT("%d"), local->tm_hour);
				counter2 = _ttoi(text);
				if (counter2 > 12) counter2 = counter2 - 12;
				SetWindowText(hh, text);
				SetTimer(hWnd,                // handle to main window 
					ID_SEC,               // timer identifier 
					1000,                     // 5-second interval 
					(TIMERPROC)NULL); // timer callback
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, rect);
		midX = rect->right / 2;
		midY = rect->bottom / 2;
		clockSize = rect->right < rect->bottom ? rect->right : rect->bottom;
		clockSize -= 100;
		r = clockSize / 2;
		wsprintf(wcs, TEXT("%d, %d, %d, %d"), rect->top, rect->right, rect->bottom, rect->left);
		SetWindowText(hWnd, wcs);

		Ellipse(hdc, midX - r, midY - r, midX + r, midY + r);
		Ellipse(hdc, midX - r + 5, midY - r + 5, midX + r - 5, midY + r - 5);
		Ellipse(hdc, midX - 15, midY - 15, midX + 15, midY + 15);
		wsprintf(wcs, TEXT("12"));
		GetTextExtentPoint32(hdc, wcs, _tcslen(wcs), tsize);
		TextOut(hdc, midX - (tsize->cx / 2), midY - r + 5, wcs, _tcslen(wcs));

		wsprintf(wcs, TEXT("3"));
		GetTextExtentPoint32(hdc, wcs, _tcslen(wcs), tsize);
		TextOut(hdc, midX + r - 5 - (tsize->cx), midY - (tsize->cy / 2), wcs, _tcslen(wcs));

		wsprintf(wcs, TEXT("6"));
		GetTextExtentPoint32(hdc, wcs, _tcslen(wcs), tsize);
		TextOut(hdc, midX - (tsize->cx / 2), midY + r - 5 - tsize->cy, wcs, _tcslen(wcs));

		wsprintf(wcs, TEXT("9"));
		GetTextExtentPoint32(hdc, wcs, _tcslen(wcs), tsize);
		TextOut(hdc, midX - r + 5, midY - (tsize->cy / 2), wcs, _tcslen(wcs));
		for (int i = 0; i < 12; i++) {
			if (i % 3 == 0) continue;
			MoveToEx(hdc, midX + (r - 15) * cos(degreesToRadians(i * 30)), midY - (r - 15) * sin(degreesToRadians(i * 30)), NULL);
			LineTo(hdc, midX + (r - 5) * cos(degreesToRadians(i * 30)), midY - (r - 5) * sin(degreesToRadians(i * 30)));
		}
		

		//Second Pointer
		MoveToEx(hdc, midX, midY, NULL);
		LineTo(hdc, midX + (r - 15) * cos(degreesToRadians(angle)), midY - (r - 15) * sin(degreesToRadians(angle)));
		MoveToEx(hdc, midX, midY, NULL);
		LineTo(hdc, midX + (r - 40) * cos(degreesToRadians(angleMIN)), midY - (r - 40) * sin(degreesToRadians(angleMIN)));
		MoveToEx(hdc, midX, midY, NULL);
		LineTo(hdc, midX + (r - 100) * cos(degreesToRadians(angleH)), midY - (r - 100) * sin(degreesToRadians(angleH)));

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case ID_SEC:
		{
			t = time(NULL);
			local = localtime(&t);
			wsprintf(text, TEXT("%d"), local->tm_sec);
			counter = _ttoi(text);
			SetWindowText(hsec, text);
			wsprintf(text, TEXT("%d"), local->tm_min);
			counter1 = _ttoi(text);
			SetWindowText(hmin, text);
			wsprintf(text, TEXT("%d"), local->tm_hour);
			counter2 = _ttoi(text);
			if (counter2 > 12) counter2 = (counter2 - 12) * 5;
			SetWindowText(hh, text);
			RECT area{ midX - (r - 10),midY - (r - 10),midX + (r + 10),midY + (r + 10) };//make app smooth;
			InvalidateRect(hWnd, &area, true);
		}
			break;
		default:
			break;
		}
		break;
    case WM_DESTROY:
		KillTimer(hWnd, tid);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
