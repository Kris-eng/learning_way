#ifndef __DRAW_CLOCK_H
#define __DRAW_CLOCK_H
#define width_k 1000
#define high_k 500
#define center_x width_k / 2
#define center_y high_k / 4
#define rr 100
#define pi 3.1415926
#include "framework.h"
#include "WindowsProject4.h"
#include "Graphic.h"
#include <math.h>
#include <time.h>
#include <graphics.h>
#include <stdio.h>
void draw_yuan(Graphic t);
void draw_dial(Graphic t);
void draw_pointer(Graphic t);
void draw_sky(Graphic t);
void draw_rainbow(Graphic t);

#endif
