#pragma once
#include <Windows.h>

enum eDirection { LEFT = 0, RIGHT, UP, DOWN };

class AsSnake
{
	int const scale{};
	const char Editing_Window = 8;
	RECT Snake_Rect{};
	HBRUSH const snake_color{}, black{};
	RECT Win_Rect{};
public:
	static eDirection dir;

	AsSnake();

	void Init(HWND hWnd);
	void Go(HDC hdc, HWND hWnd);
	int On_Time(HWND hWnd) const;
private:
	void Movement(eDirection &dir);
};

