#pragma once
#include "Config.h"
#include <cstdlib> // ��� ������� rand() � srand()
#include <ctime> // ��� ������� time()

class AsApple
{

public:
	bool does_not_have_an_apple = true;//�� �� ������?
	
	const HPEN Apple_Col_Pen{};
	const HBRUSH Apple_Col_Brush{};
	RECT Apple_Rect{};

	AsApple();

	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Spawn(HWND hWnd, int width, int height, vector<vector<bool>> Level);
	bool Eat(RECT snk_rek);
private:
};