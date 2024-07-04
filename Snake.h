#pragma once
#include "Apple.h"

enum eDirection { LEFT = 0, RIGHT, UP, DOWN, UNK};
enum eState{LIFE = 0, DEAD, GAMEOVER};

class AsSnake
{
	unsigned int tail_length = 20;
public:

	RECT Rect{};

	const HPEN Color_Pen_life{};
	const HBRUSH Color_Brush_life{};
	const HPEN Color_Pen_dead{};
	const HBRUSH Color_Brush_dead{};
	HPEN Color_Pen_now{};
	HBRUSH Color_Brush_now{};

	std::list <RECT> body;

	static eDirection dir;
	static eState state;
	AsSnake();

	unsigned int get_tail_length() const;

	void Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect);
	void Movement(HWND hWnd, int width, int height, eState state, AsApple &Apple);
private:
	void Tail(HWND hWnd);
	void Head(HWND hWnd, int width, int height, AsApple &Apple);
	void Autocannibalism(RECT rect);
};