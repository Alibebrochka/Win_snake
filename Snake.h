#pragma once
#include "Apple.h"

enum eDirection { LEFT = 0, RIGHT, UP, DOWN, UNK};

class AsSnake
{
	int Width{}, Height{};

	unsigned short tail_length{1};
	RECT Snake_Rect{}, Win_Rect{};
	std::list <RECT> body;

	vector<vector<bool>> Level;

	const char Editing_Window = 8;
	const HPEN Snake_Color_Pen{}, BG_Pen{};
	const HBRUSH Snake_Color_Brush{}, BG_Brush{};

public:
	static eDirection dir;
	AsSnake();

	void Init(HWND hWnd, RECT Start_Win);
	void Go(HDC hdc, HWND hWnd);
	int On_Time(HWND hWnd);
private:
	void entry(int rows, int columns, bool b);

	void Movement(HWND hWnd, int width, int height);
	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Tail(HWND hWnd);
	void Head(HWND hWnd, int width, int height);
	void Autocannibalism(RECT rect);

	AsApple Apple{};
};