#pragma once
#include "Config.h"
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()

class AsApple
{

public:
	bool does_not_have_an_apple = true;//яблука не має
	
	const HPEN Col_Pen{};
	const HBRUSH Col_Brush{};
	RECT Rect{};

	AsApple();

	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Spawn(HWND hWnd, int width, int height, vector<vector<bool>> Map);
	bool Eat(RECT snk_rek);
private:
};