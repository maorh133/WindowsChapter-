#include <Windows.h>
#include <string>
#include <stdio.h>
#include <fstream>
#pragma warning(disable : 4996)
#define INFO_BUFFER_SIZE 32767

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM IParam)
{
	static int count = 0;
	char  countInString[10] = { 0 };
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		count++;
		break;
	case WM_RBUTTONDOWN:
		_itoa(count, countInString, 10);
		SetWindowText(hWnd, countInString);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_RETURN)
		{
			char date[15] = { 0 };
			char time[15] = { 0 };
			SYSTEMTIME st;
			GetLocalTime(&st);
			GetDateFormat(0, DATE_SHORTDATE, &st, NULL, date, sizeof(date));
			GetTimeFormat(0, LOCALE_NOUSEROVERRIDE, &st, NULL, time, sizeof(time));
			std::ofstream out;
			// std::ios::app is the open mode "append" meaning
			// new data will be written to the end of the file.
			out.open("TimeOfEnters.txt", std::ios::app);
			out << date <<" " << time << std::endl;
			out.close();
		}
		break;
	default:
	break;
	}
	return DefWindowProc(hWnd, msg, wParam, IParam);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	TCHAR  infoBuf[INFO_BUFFER_SIZE];

	//Get Windows Directory
	GetWindowsDirectory(infoBuf, INFO_BUFFER_SIZE);
	MessageBox(NULL, TEXT(infoBuf), "Windows Directory", MB_OK);
	
	WNDCLASS wc = { 0 };
	MSG msg = { 0 };
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = "Maor Class";
	wc.hInstance = hInstance;

	if (FALSE == RegisterClass(&wc))
	{
		MessageBox(NULL, "RegisterClass ERROR", "ERROR",MB_OK |MB_ICONWARNING);
		return -1;
	}

	HWND hWnd = CreateWindow(TEXT(wc.lpszClassName), TEXT("Maor"), WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hInstance, NULL);
	if (NULL == hWnd)
	{
		DWORD a = GetLastError();
		MessageBox(NULL, "hWnd ERROR", "ERROR", MB_OK | MB_ICONWARNING);
		return -1;
	}
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
