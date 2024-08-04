#pragma once
#include "Snake.h"

class AsEngine {
	int Width{}, Height{};
	const char Editing_Window = 8;

public:
	static vector<vector<int>> Map;

	RECT Win_Rect{};

	void Init(HWND hWnd, RECT Start_Win);
	void Draw(HDC hdc, HWND hWnd);
	int On_Time(HWND hWnd);

	static void entry(int rows, int columns, int b);
private:
	AsSnake Snake;
	AsApple Apple;
	AsHell* Hell;
};