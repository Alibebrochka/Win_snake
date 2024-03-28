#pragma once
#include "Apple.h"
#include <list>

enum eDirection { LEFT = 0, RIGHT, UP, DOWN };

class AsSnake
{
	short tail_length{};
	RECT Snake_Rect{}, Win_Rect{};
	std::list <RECT> body;

	const char Editing_Window = 8;
	const HPEN Snake_Color_Pen{}, BG_Pen{};
	const HBRUSH Snake_Color_Brush{}, BG_Brush{};

public:
	static eDirection dir;
	AsSnake();

	void Init(HWND hWnd);
	void Go(HDC hdc, HWND hWnd);
	int On_Time(HWND hWnd) ;
private:
	void Movement(HWND hWnd, int width, int height);
	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Tail(HWND hWnd);
	void Head(HWND hWnd, int width, int height);

	AsApple Apple{};
};