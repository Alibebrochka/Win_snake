#pragma once
#include "Apple.h"

enum eDirection { LEFT = 0, RIGHT, UP, DOWN, UNK};

class AsSnake
{
	unsigned int tail_length = 1;
public:

	RECT Rect{};

	const HPEN Color_Pen{};
	const HBRUSH Color_Brush{};

	std::list <RECT> body;
	static eDirection dir;
	AsSnake();

	unsigned int get_tail_length() const;

	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Movement(HWND hWnd, int width, int height, AsApple &Apple);
private:
	void Tail(HWND hWnd);
	void Head(HWND hWnd, int width, int height, AsApple &Apple);
	void Autocannibalism(RECT rect);
};