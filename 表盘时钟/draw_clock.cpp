#include "draw_colck.h"
#include "Graphic.h"

extern Graphic t;
SYSTEMTIME ti;
void draw_yuan(Graphic t)
{
    t.SelectAPen(PS_SOLID, 1, RGB(136, 134, 135));
    t.SelectABrush(RGB(251, 241, 4));
    t.DrawCircle(center_x, center_y, rr);
}
void draw_dial(Graphic t)
{

	for (int i = 0; i < 60; i++)
	{
		float angle = 2 * pi / 60 * i;
		float start_x, start_y, end_x, end_y;
		// cout << angle<<endl;
		if (i % 5 == 0)
		{
			t.SelectAPen(PS_SOLID, 3, RGB(0, 0, 0));

			start_x = center_x + (rr - 12) * cos(angle - pi / 2);
			start_y = center_y + (rr - 12) * sin(angle - pi / 2);
			end_x = center_x + (rr - 3) * cos(angle - pi / 2);
			end_y = center_y + (rr - 3) * sin(angle - pi / 2);
		}
		else
		{
			t.SelectAPen(PS_SOLID, 1, RGB(0, 0, 0));
			
			start_x = center_x + (rr - 8) * cos(angle - pi / 2);
			start_y = center_y + (rr - 8) * sin(angle - pi / 2);
			end_x = center_x + (rr - 3) * cos(angle - pi / 2);
			end_y = center_y + (rr - 3) * sin(angle - pi / 2);
		}
		// cout << end_x <<"  " <<start_x<< endl;
		t.DrawLine(start_x, start_y, end_x, end_y);
		// cout << start_x << "  " << start_y << "  " << end_x << "  " << end_y << endl;
	}

}


void draw_hour_pointer(Graphic t,int hour)
{
	t.SelectAPen(PS_SOLID, 5, RGB(0, 0, 0));
	hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 12 * hour;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (rr - 45) * cos(angle - pi / 2);
	end_y = center_y + (rr - 45) * sin(angle - pi / 2);
	t.DrawLine(start_x, start_y, end_x, end_y);
}
void draw_min_pointer(Graphic t, int min)
{
	t.SelectAPen(PS_SOLID, 3, RGB(0, 0, 0));
	// hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 60 * min;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (rr - 20) * cos(angle - pi / 2);
	end_y = center_y + (rr - 20) * sin(angle - pi / 2);
	t.DrawLine(start_x, start_y, end_x, end_y);
}

void draw_second(Graphic t ,int sec)
{
	t.SelectAPen(PS_SOLID, 1.3, RGB(248, 61, 26));
	// hour = hour > 12 ? hour - 12 : hour;
	float angle = 2 * pi / 60 * sec;
	float start_x, start_y, end_x, end_y;

	start_x = center_x;
	start_y = center_y;
	end_x = center_x + (rr - 10) * cos(angle - pi / 2);
	end_y = center_y + (rr - 10) * sin(angle - pi / 2);
	t.DrawLine(start_x, start_y, end_x, end_y);
}

void draw_pointer(Graphic t)
{
	GetLocalTime(&ti);
	draw_hour_pointer(t, ti.wHour);
	draw_min_pointer(t, ti.wMinute);
	draw_second(t, ti.wSecond);
}

void draw_rainbow(Graphic t)
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
	(PS_SOLID, 2);
	for (int q = 400; q > 344; q--)
	{
		H += 5;
		//t.SelectAFont();
		//t.SelectABrush(NULL);
		t.SelectAPen(PS_SOLID, 1.3,HSLtoRGB(H, S, L));
		t.DrawCircle(500, 480, q);
	}
}
void draw_sky(Graphic t)
{
	float H = 190;
	float S = 1;
	float L = 0.7f;
	for (int y = 0; y < 480; y++)
	{
		L += 0.0005f;
		t.SelectAPen(PS_SOLID,1,HSLtoRGB(H, S, L));
		t.DrawLine(0, y, width_k, y);
	}
}

