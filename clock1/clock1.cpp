#include <iostream>
#include <math.h>
#include <graphics.h>
#include "clock1.h"
#include <string.h>
#include <conio.h>
//#include<sstream>
using namespace std;
// IMAGE backgrand;

#define width 1000
#define high 500
#define center_x width / 2
#define center_y high / 4
#define r 100
#define pi 3.1415926

void out_nameandnumber(void);
class TDZ
{
public:
	void draw_yuan(void);
	void draw_dial(void);
	void draw_pointer(void);
	void draw_hour_pointer(int hour);
	void draw_min_pointer(int min);
	void draw_second(int sec);
	void put_time();

private:
	SYSTEMTIME ti;
};

class rainbow
{
public:
	rainbow()
	{
		draw_sky();
		draw_rainbow();
	}
	void draw_rainbow();
	void draw_sky();
};

int main(void)
{

	IMAGE backgrand;
	// loadimage(&backgrand,L"./0.jpg");
	initgraph(width, high, SHOWCONSOLE);
	setbkcolor(WHITE);
	// setbkmode(TRANSPARENT);
	putimage(0, 0, &backgrand);
	cleardevice();
	TDZ t;
	rainbow bk;
	// s_qune();
	out_nameandnumber();
	while (1)
	{
		/*draw_yuan();
		draw_dial();
		draw_pointer();*/
		BeginBatchDraw();
		t.draw_yuan();
		t.draw_dial();

		t.draw_pointer();
		t.put_time();

		FlushBatchDraw();
		EndBatchDraw();
	}
	// line(10, 10, 500, 500);
	// cout << cos(3.1415926);
	system("pause");
	return 0;
}

void TDZ::draw_yuan(void)
{

	setlinecolor(RGB(136, 134, 135));
	// setlinestyle(PS_SOLID, 5);
	setfillcolor(RGB(251, 241, 4));
	fillcircle(center_x, center_y, r);
}
void TDZ::draw_dial()
{
	setlinecolor(BLUE);
	setlinestyle(PS_SOLID, 3);
	for (int i = 0; i < 60; i++)
	{
		float angle = 2 * pi / 60 * i;
		float start_x, start_y, end_x, end_y;
		// cout << angle<<endl;
		if (i % 5 == 0)
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 3);
			start_x = center_x + (r - 12) * cos(angle - pi / 2);
			start_y = center_y + (r - 12) * sin(angle - pi / 2);
			end_x = center_x + (r - 3) * cos(angle - pi / 2);
			end_y = center_y + (r - 3) * sin(angle - pi / 2);
		}
		else
		{
			setlinecolor(BLACK);
			setlinestyle(PS_SOLID, 1);
			start_x = center_x + (r - 8) * cos(angle - pi / 2);
			start_y = center_y + (r - 8) * sin(angle - pi / 2);
			end_x = center_x + (r - 3) * cos(angle - pi / 2);
			end_y = center_y + (r - 3) * sin(angle - pi / 2);
		}
		// cout << end_x <<"  " <<start_x<< endl;
		line(start_x, start_y, end_x, end_y);
		// cout << start_x << "  " << start_y << "  " << end_x << "  " << end_y << endl;
	}
}

void TDZ::draw_pointer(void)
{
	GetLocalTime(&ti);
	draw_hour_pointer(ti.wHour);
	draw_min_pointer(ti.wMinute);
	draw_second(ti.wSecond);
}

void TDZ::draw_hour_pointer(int hour)
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);
	hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 12 * hour;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (r - 45) * cos(angle - pi / 2);
	end_y = center_y + (r - 45) * sin(angle - pi / 2);
	line(start_x, start_y, end_x, end_y);
}
void TDZ::draw_min_pointer(int min)
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 3);
	// hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 60 * min;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (r - 20) * cos(angle - pi / 2);
	end_y = center_y + (r - 20) * sin(angle - pi / 2);
	line(start_x, start_y, end_x, end_y);
}

void TDZ::draw_second(int sec)
{
	setlinecolor(RGB(248, 61, 26));
	setlinestyle(PS_SOLID, 1.3);
	// hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 60 * sec;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (r - 10) * cos(angle - pi / 2);
	end_y = center_y + (r - 10) * sin(angle - pi / 2);
	line(start_x, start_y, end_x, end_y);
}

void TDZ::put_time()
{
	char hour[30], minute[30], sec[30];
	if(ti.wHour>=10)
	sprintf_s(hour, "%d", ti.wHour);
	else
	{
		char time[30] = "0" ;
		sprintf_s(hour, "%d", ti.wHour);
		strcat_s(time, hour);
		strcpy_s(hour, time);
	}
	if (ti.wMinute>=10)
	sprintf_s(minute, "% d", ti.wMinute);
	else
	{
		char time[30] = "0";
		sprintf_s(minute, "%d", ti.wMinute);
		strcat_s(time, minute);
		strcpy_s(minute, time);
	}
	if(ti.wSecond>=10)
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

	settextcolor(RGB(255, 127, 39));
	settextstyle(50, 0, "楷体");
	outtextxy(290, 300, "pm");
	outtextxy(340, 300, hour);
	cout << ti.wSecond <<"" << hour << endl;
}
void out_nameandnumber(void)
{
	settextcolor(RGB(255, 174, 201));
	settextstyle(20, 0, "楷体");
	outtextxy(800, 450, "2003070227谭德众");
}
void rainbow::draw_rainbow()
{

	float H = 190;
	float S = 1;
	float L = 0.7f;
	// for (int y = 0; y < 480; y++)
	//{
	//	L += 0.0005f;
	//	setlinecolor(HSLtoRGB(H, S, L));
	//	line(0, y, width, y);
	// }
	H = 0;
	S = 1;
	L = 0.5f;
	setlinestyle(PS_SOLID, 2);
	for (int q = 400; q > 344; q--)
	{
		H += 5;
		setlinecolor(HSLtoRGB(H, S, L));
		circle(500, 480, q);
	}
}
void rainbow::draw_sky()
{
	float H = 190;
	float S = 1;
	float L = 0.7f;
	for (int y = 0; y < 480; y++)
	{
		L += 0.0005f;
		setlinecolor(HSLtoRGB(H, S, L));
		line(0, y, width, y);
	}
}
