#include "PoDefinition.h"
#include "PoMath.h"
#include "PoUtilities.h"
#include "PoInput.h"
#include "PoAudio.h"
#include "PoGraphics.h"
#include "PoUI.h"

HWND hwnd;
HINSTANCE hinstance;
MSG msg;
HRESULT CALLBACK WindowProc(HWND _hwnd, UINT message, WPARAM wparam, LPARAM lParam)
{
	switch (message)
	{
		case WM_SIZE:
		{
			resizewindow = 1;
		}break;
		case WM_GETMINMAXINFO:
		{
			LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
			lpMMI->ptMinTrackSize.x = screenwidthmin;
			lpMMI->ptMinTrackSize.y = screenheightmin;
		}break;
		case WM_DESTROY:
		{
			escape = 1;
			PostQuitMessage(0);
			return 0;
		} break;
	}
	//void WindowsInterrupt(UINT message, WPARAM wparam, LPARAM lParam);
	//WindowsInterrupt(message, wparam, lParam);
	return (HRESULT)DefWindowProc(_hwnd, message, wparam, lParam);
}
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	UNREFERENCED_PARAMETER(_nCmdShow);
	UNREFERENCED_PARAMETER(_lpCmdLine);
	UNREFERENCED_PARAMETER(_hPrevInstance);
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	hinstance = _hInstance;

	LARGE_INTEGER t;
	QueryPerformanceFrequency(&t);
	frequency = t.QuadPart;
	timeBeginPeriod(1);

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;// CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	wc.hInstance = hinstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = "PO";
	wc.hIcon = LoadIconA(hinstance, MAKEINTRESOURCEA(101));
	RegisterClassEx(&wc);
	hwnd = CreateWindowEx(NULL, "PO", "PO", WS_OVERLAPPEDWINDOW, GetSystemMetrics(SM_CXSCREEN)/2 - screenwidth/2, GetSystemMetrics(SM_CYSCREEN) / 2 - screenheight / 2, screenwidth, screenheight, NULL, NULL, hinstance, NULL);
	if (hwnd == NULL) { MessageBox(hwnd, "Failed To Build Window", "FATAL Error", MB_OK);	return (int)msg.wParam; }
	HCURSOR hcursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hcursor);
	//ShowCursor(FALSE);
	//ShowWindow(hwnd, SW_SHOW);
	ShowWindow(hwnd, STARTWINDOWSTATE);
	timeEndPeriod(1);

	void Main();
	Main();
	
	ShowWindow(hwnd, SW_HIDE);
	Sleep(200);
	_CrtDumpMemoryLeaks();
	return (int)msg.wParam;
}
bool Loop()
{
	timemain.Update();
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
			return false;
	}
	return true;
}
/*
void WindowsInterrupt(UINT message, WPARAM wparam, LPARAM lparam)
{
	(lparam);
	switch (message)
	{
	case WM_KEYDOWN:
	{
		if (console)
		{
			switch (wparam)
			{
			case 0x41:strcat_s(commandconsole->line[0], "a"); break;
			case 0x42:strcat_s(commandconsole->line[0], "b"); break;
			case 0x43:strcat_s(commandconsole->line[0], "c"); break;
			case 0x44:strcat_s(commandconsole->line[0], "d"); break;
			case 0x45:strcat_s(commandconsole->line[0], "e"); break;
			case 0x46:strcat_s(commandconsole->line[0], "f"); break;
			case 0x47:strcat_s(commandconsole->line[0], "g"); break;
			case 0x48:strcat_s(commandconsole->line[0], "h"); break;
			case 0x49:strcat_s(commandconsole->line[0], "i"); break;
			case 0x4A:strcat_s(commandconsole->line[0], "j"); break;
			case 0x4B:strcat_s(commandconsole->line[0], "k"); break;
			case 0x4C:strcat_s(commandconsole->line[0], "l"); break;
			case 0x4D:strcat_s(commandconsole->line[0], "m"); break;
			case 0x4E:strcat_s(commandconsole->line[0], "n"); break;
			case 0x4F:strcat_s(commandconsole->line[0], "o"); break;
			case 0x50:strcat_s(commandconsole->line[0], "p"); break;
			case 0x51:strcat_s(commandconsole->line[0], "q"); break;
			case 0x52:strcat_s(commandconsole->line[0], "r"); break;
			case 0x53:strcat_s(commandconsole->line[0], "s"); break;
			case 0x54:strcat_s(commandconsole->line[0], "t"); break;
			case 0x55:strcat_s(commandconsole->line[0], "u"); break;
			case 0x56:strcat_s(commandconsole->line[0], "v"); break;
			case 0x57:strcat_s(commandconsole->line[0], "w"); break;
			case 0x58:strcat_s(commandconsole->line[0], "x"); break;
			case 0x59:strcat_s(commandconsole->line[0], "y"); break;
			case 0x5A:strcat_s(commandconsole->line[0], "z"); break;

			case 0x60:strcat_s(commandconsole->line[0], "0"); break;
			case 0x61:strcat_s(commandconsole->line[0], "1"); break;
			case 0x62:strcat_s(commandconsole->line[0], "2"); break;
			case 0x63:strcat_s(commandconsole->line[0], "3"); break;
			case 0x64:strcat_s(commandconsole->line[0], "4"); break;
			case 0x65:strcat_s(commandconsole->line[0], "5"); break;
			case 0x66:strcat_s(commandconsole->line[0], "6"); break;
			case 0x67:strcat_s(commandconsole->line[0], "7"); break;
			case 0x68:strcat_s(commandconsole->line[0], "8"); break;
			case 0x69:strcat_s(commandconsole->line[0], "9"); break;

			case 0x30:strcat_s(commandconsole->line[0], "0"); break;
			case 0x31:strcat_s(commandconsole->line[0], "1"); break;
			case 0x32:strcat_s(commandconsole->line[0], "2"); break;
			case 0x33:strcat_s(commandconsole->line[0], "3"); break;
			case 0x34:strcat_s(commandconsole->line[0], "4"); break;
			case 0x35:strcat_s(commandconsole->line[0], "5"); break;
			case 0x36:strcat_s(commandconsole->line[0], "6"); break;
			case 0x37:strcat_s(commandconsole->line[0], "7"); break;
			case 0x38:strcat_s(commandconsole->line[0], "8"); break;
			case 0x39:strcat_s(commandconsole->line[0], "9"); break;

			case VK_OEM_MINUS:strcat_s(commandconsole->line[0], "-"); break;
			case VK_SUBTRACT:strcat_s(commandconsole->line[0], "-"); break;
			case VK_OEM_PLUS:strcat_s(commandconsole->line[0], "+"); break;
			case VK_ADD:strcat_s(commandconsole->line[0], "+"); break;
			case VK_SPACE:strcat_s(commandconsole->line[0], " "); break;
			case VK_OEM_PERIOD:strcat_s(commandconsole->line[0], "."); break;
			case VK_BACK:for (UINT8 c = 1; c < BUFFERSIZE; c++)if (commandconsole->line[0][c] == 0 && c > 1) { commandconsole->line[0][c - 1] = 0; break; }break;
			case VK_RETURN: commandconsole->Command(commandconsole->line[0]); break;
			}
		}
		switch (wparam)
		{
		case VK_TAB:if (console)console = false; else console = true; break;
			//case 0x50:if (pause)pause = false; else pause = true; break;
		}
	}
	break;
	case WM_KEYUP:
	{

	}
	break;
	}
}
*/

