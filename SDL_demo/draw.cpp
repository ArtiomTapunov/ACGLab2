#include "draw.h"
#include "stdafx.h"

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)
#define PI 3.14159265
#include "iostream"
#include <vector>
using namespace std;



void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	assert(NULL != surface);
	assert(x < SCREEN_WIDTH);
	assert(y < SCREEN_HEIGHT);

	Uint32 *pixels = (Uint32 *)surface->pixels;
	pixels[(y * surface->w) + x] = pixel;
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
	assert(NULL != surface);
	assert(x < SCREEN_WIDTH);
	assert(y < SCREEN_HEIGHT);

	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}

int getY(int x, int a){
	double expression = (( x * x * x ) / (x - a)) * -1;
	return (int) sqrt(abs(expression));
}

void drawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel){
	int i;
	double x = x1 - x0;
	double y = y1 - y0;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;

	x = x0;
	y = y0;

	for(int i = 0; i < length; i += 1){
		put_pixel32(Screen, x, y, pixel);
		x += addx;
		y += addy;
	}
}

void drawRectangle(SDL_Surface *s, int x0, int y0, int x1, int y1, Uint32 pixel){
	drawLine(s, x0, y0, x0, y1, RGB(255, 255, 255));
	drawLine(s, x0, y0, x1, y0, RGB(255, 255, 255));
	drawLine(s, x1, y0, x1, y1, RGB(255, 255, 255));
	drawLine(s, x0, y1, x1, y1, RGB(255, 255, 255));
}

double newX(double x, double x1, double m)
{
	return ((1 - m)*x + m*x1);
}

double newY(double y, double y1, double m)
{
	return ((1 - m)*y + m*y1);
}

void draw(SDL_Surface *s, double step)
{
	vector<int[2]> shape;
	vector <int[2]> newShape;
	int x1 = 10;
	int y1 = 10;
	int x2 = 300;
	int y2 = 300;
	//double angle = 15.0;
	double m = step;
	int sqrCount = 5;

	drawRectangle(s, x1, y1, x2, y2, RGB(100, 98, 21));
	//double k = tan(angle * PI / 180.0);

	//drawLine(s, 160, 160, newX(10, 300, 0.1), newY(10, 10, 0.1), RGB(255, 255, 255));

	int X1 = newX(x1, x2, m);
	int Y1 = newY(y1, y1, m);

	int X2 = newX(x2, x2, m);
	int Y2 = newY(y1, y2, m);

	int X3 = newX(x2, x1, m);
	int Y3 = newY(y2, y2, m);

	int X4 = newX(x1, x1, m);
	int Y4 = newY(y2, y1, m);

	drawLine(s, X1, y1, X2, Y2, RGB(255, 255, 255));
	drawLine(s, X2, Y2, X3, y2, RGB(255, 255, 255));
	drawLine(s, X3, y2, x1, Y4, RGB(255, 255, 255));
	drawLine(s, x1, Y4, X1, y1, RGB(255, 255, 255));

	for (int i = 0; i < sqrCount; i++)
	{
		X1 = newX(X1, X2, m);
		Y1 = newY(Y1, Y2, m);

		X2 = newX(X2, X3, m);
		Y2 = newY(Y2, Y3, m);

		X3 = newX(X3, X4, m);
		Y3 = newY(Y3, Y4, m);

		X4 = newX(X4, X1, m);
		Y4 = newY(Y4, Y1, m);

		drawLine(s, X1, Y1, X2, Y2, RGB(255, 255, 255));
		drawLine(s, X2, Y2, X3, Y3, RGB(255, 255, 255));
		drawLine(s, X3, Y3, X4, Y4, RGB(255, 255, 255));
		drawLine(s, X4, Y4, X1, Y1, RGB(255, 255, 255));
	}
	//cout << tan(15.0 * PI / 180.0)<< endl;
		//for (int j = 100; j < 180; j++)
			//put_pixel32(s, x, j, RGB32(0, 255, 0));
	
	// или использу€ макрос можно получить код цвета:
	//   RGB32(0, 255, 0) эквивалентно записи 0x0000FF00
}




