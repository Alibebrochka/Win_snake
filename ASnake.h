#pragma once
#include <Windows.h>
#include <list>

enum eDirection { LEFT = 0, RIGHT, UP, DOWN };

class AsSnake
{
	int tail_length{10};
	RECT Snake_Rect{}, Win_Rect{};
	std::list <RECT> body;

	int const scale{};
	const char Editing_Window = 8;
	HBRUSH const snake_color{}, black{};

public:
	static eDirection dir;
	AsSnake();

	void Init(HWND hWnd);
	void Go(HDC hdc, HWND hWnd);
	int On_Time(HWND hWnd) ;
private:
	void Draw(HDC hdc, HBRUSH hbrush, RECT rect);
	void Head();
	void Tail(HWND hWnd);
	void Movement(HWND hWnd);
	void Teleport_Head(HWND hWnd);
};

