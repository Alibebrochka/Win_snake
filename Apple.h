#pragma once
#include "Config.h"
#include <cstdlib> // для функций rand() и srand()

class AsHell
{
public:
	virtual void Port() = 0;
};

class AsApple
{
	static const HPEN Color_Pen_normal;
	static const HBRUSH Color_Brush_normal;
	static const HPEN Color_Pen_in_hell;
	static const HBRUSH Color_Brush_in_hell;

public:
	bool does_not_have_an_apple = true;//яблука не має?
	
	static HPEN Color_Pen_now;
	static HBRUSH Color_Brush_now;

	RECT Rect{};

	AsApple();

	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Spawn(HWND hWnd, int width, int height, vector<vector<int>> Map, AsHell* Hell);
	bool Eat(RECT snk_rek);
	static void In_Hell();
};