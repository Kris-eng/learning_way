// WindowsProject4.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject4.h"
#include "Graphic.h"
#include "draw_colck.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LOADSTRING 100
void put_time(HDC hdc);

void drawaa_rect(HDC hdc);
#include <windows.h> 
#include <math.h> 
#define ID_TIMER 1 
#define TWOPI (2 * 3.14159) 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("Clock");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, TEXT("Analog Clock"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		width_k, high_k,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
void SetIsotropic(HDC hdc, int cxClient, int cyClient)
{
	SetMapMode(hdc, MM_ISOTROPIC);
	SetWindowExtEx(hdc, 1000, 1000, NULL);
	//Defoe.Tu tyysoft@yahoo.com.cn Windows 程序设计 PDF 美化版
	SetViewportExtEx(hdc, cxClient / 2, -cyClient / 2, NULL);
	SetViewportOrgEx(hdc, cxClient / 2, cyClient / 2, NULL);
}
void RotatePoint(POINT pt[], int iNum, int iAngle)
{
	int i;
	POINT ptTemp;

	for (i = 0; i < iNum; i++)
	{
		ptTemp.x = (int)(pt[i].x * cos(TWOPI * iAngle / 360) +
			pt[i].y * sin(TWOPI * iAngle / 360));

		ptTemp.y = (int)(pt[i].y * cos(TWOPI * iAngle / 360) -
			pt[i].x * sin(TWOPI * iAngle / 360));

		pt[i] = ptTemp;
	}
}
void DrawClock(HDC hdc)
{
	int iAngle;
	POINT pt[3];
	for (iAngle = 0; iAngle < 360; iAngle += 6)
	{
		pt[0].x = 0;
		pt[0].y = 900;

		RotatePoint(pt, 1, iAngle);

		pt[2].x = pt[2].y = iAngle % 5 ? 33 : 100;

		pt[0].x -= pt[2].x / 2;
		pt[0].y -= pt[2].y / 2;

		pt[1].x = pt[0].x + pt[2].x;
		pt[1].y = pt[0].y + pt[2].y;

		SelectObject(hdc, GetStockObject(BLACK_BRUSH));
		Ellipse(hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
	}
}
void DrawHands(HDC hdc, SYSTEMTIME* pst, BOOL fChange)
{
	static POINT pt[3][5] = { 0, -150, 100, 0, 0, 600, -100, 0, 0, -150,
	0, -200, 50, 0, 0, 800, -50, 0, 0,-200,
	0,0, 0, 0, 0, 0, 0, 0, 0, 800 };
	int i, iAngle[3];
	POINT ptTemp[3][5];

	iAngle[0] = (pst->wHour * 30) % 360 + pst->wMinute / 2;
	iAngle[1] = pst->wMinute * 6;
	iAngle[2] = pst->wSecond * 6;

	memcpy(ptTemp, pt, sizeof(pt));
	for (i = fChange ? 0 : 2; i < 3; i++)
	{
		RotatePoint(ptTemp[i], 5, iAngle[i]);
		Polyline(hdc, ptTemp[i], 5);
	}
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	static SYSTEMTIME stPrevious;
	//Defoe.Tu tyysoft@yahoo.com.cn Windows 程序设计 PDF 美化版
	BOOL fChange;
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hwnd, ID_TIMER, 1000, NULL);
		GetLocalTime(&st);
		stPrevious = st;
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_TIMER:
	{
		GetLocalTime(&st);
		fChange = st.wHour != stPrevious.wHour ||
			st.wMinute != stPrevious.wMinute;

		hdc = GetDC(hwnd);
		Graphic t2(hdc);
		draw_yuan(t2);
		draw_dial(t2);
		drawaa_rect(hdc);
		put_time(hdc);
		draw_pointer(t2);
	/*	draw_yuan(t2);
		draw_dial(t2);
		draw_pointer(t2);
		put_time(hdc);*/
		//draw_yuan(t2);
		/*SetIsotropic(hdc, cxClient, cyClient);
		SelectObject(hdc, GetStockObject(WHITE_PEN));
		DrawHands(hdc, &stPrevious, fChange);
		
		SelectObject(hdc, GetStockObject(BLACK_PEN));
		DrawHands(hdc, &st, TRUE);*/
		ReleaseDC(hwnd, hdc);

		stPrevious = st;
		return 0;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		Graphic t(hdc);
		//draw_rainbow(t);
		draw_sky(t);
		draw_rainbow(t);
		draw_yuan(t);
		draw_dial(t);
		
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY:
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

void put_time(HDC hdc)
{
	SYSTEMTIME ti;
	RECT rect;
	Graphic a(hdc);
	GetLocalTime(&ti);
	char hour[30], minute[30], sec[30];
	if (ti.wHour >= 10)
		sprintf_s(hour, "%d", ti.wHour);
	else
	{
		char time[30] = "0";
		sprintf_s(hour, "%d", ti.wHour);
		strcat_s(time, hour);
		strcpy_s(hour, time);
	}
	if (ti.wMinute >= 10)
		sprintf_s(minute, "% d", ti.wMinute);
	else
	{
		char time[30] = "0";
		sprintf_s(minute, "%d", ti.wMinute);
		strcat_s(time, minute);
		strcpy_s(minute, time);
	}
	if (ti.wSecond >= 10)
		sprintf_s(sec, "%d", ti.wSecond);
	else
	{
		char time[30] = "0";
		sprintf_s(sec, "%d", ti.wSecond);
		strcat_s(time, sec);
		strcpy_s(sec, time);
	}
	//cout << ti.wDay;

	strcat_s(hour, ":");
	strcat_s(hour, minute);
	strcat_s(hour, ":");
	strcat_s(hour, sec);

	rect.left = 300;
	rect.right = 700;
	rect.bottom = 500;
	rect.top = 300;
	//Sette
	SetTextColor(hdc,RGB(255, 174, 201));
	//SetTextJustification(hdc,)
	//TextOut(hdc, 0, 0, hour, sizeof(hour));
	a.SelectAFont("宋体",26,true, true);
	a.SetTextColor(RGB(255, 174, 201));
	a.FillRect(rect, RGB(255, 255, 255));
	a.DrawTextA(hour, rect);
	///*outtext()
	/*settextstyle(50, 0, "楷体");
	outtextxy(290, 300, "pm");
	outtextxy(340, 300, hour);*/
	//cout << ti.wSecond << "" << hour << endl;*/
}

void drawaa_rect(HDC hdc)
{
	Graphic b(hdc);

	b.DrawRect(300, 700, 500, 200, true);


}