#include "Snake.h"

AsSnake::AsSnake():
Snake_Color_Pen(CreatePen(PS_SOLID, 0, RGB(255, 255, 255))),
Snake_Color_Brush(CreateSolidBrush(RGB(255, 255, 255))),
BG_Pen(CreatePen(PS_SOLID, 0, RGB(0, 0, 0))),
BG_Brush(CreateSolidBrush(RGB(0, 0, 0)))
{}

eDirection AsSnake::dir = DOWN;

void AsSnake::Init(HWND hWnd, RECT Start_Win)
{
	srand(static_cast<unsigned int>(time(0)));

	Width = (Start_Win.left + Start_Win.right - Editing_Window) - (Start_Win.left + Editing_Window);
	Height = (Start_Win.top + Start_Win.bottom) - (Start_Win.top + Editing_Window);

	Level = vector<vector<bool>>(Height / AsConfig::scale, vector<bool>(Width / AsConfig::scale, true));

	Snake_Rect.left = 0 /*width / 2 - AsConfig::scale*/;
	Snake_Rect.right = Snake_Rect.left + AsConfig::scale;
	Snake_Rect.top = 0/*height / 2 - AsConfig::scale*/;
	Snake_Rect.bottom = Snake_Rect.top + AsConfig::scale;

	body.push_back(Snake_Rect);
	entry(body.back().top, body.back().left, false);
	
	SetTimer(hWnd, WM_USER + 1, 75, 0);
}

void AsSnake::Go(HDC hdc, HWND hWnd)
{
	if (dir == UNK){
		;
	}
	else {
		if (Apple.does_not_have_an_apple)
			Apple.Draw(hdc, BG_Brush, BG_Pen, Apple.Apple_Rect);
		else
			Apple.Draw(hdc, Apple.Apple_Col_Brush, Apple.Apple_Col_Pen, Apple.Apple_Rect);

		Draw(hdc, Snake_Color_Brush, Snake_Color_Pen, Snake_Rect);

		if (body.size() > tail_length) {
			Draw(hdc, BG_Brush, BG_Pen, body.front());
			entry(body.front().top, body.front().left, true);
			body.pop_front();
		}
	}
}

int AsSnake::On_Time(HWND hWnd) 
{
	GetWindowRect(hWnd, &Win_Rect);
	int width_new = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height_new = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	if (Width != width_new || Height != height_new) {
		Width = width_new;
		Height = height_new;
		Level.resize(Height / AsConfig::scale, vector<bool>(Width, true));
		for (auto& x : Level) {
			x.resize(Width / AsConfig::scale, true);
		}
	}

	Apple.Spawn(hWnd, Width, Height, Level);
	if (dir != UNK)
		Movement(hWnd, Width, Height);
	return 0;
}

void AsSnake::entry(int rows, int columns, bool b)
{
	Level[rows / AsConfig::scale][columns / AsConfig::scale] = b;
}

void AsSnake::Movement(HWND hWnd, int width, int height)
{
	Tail(hWnd);
	Head(hWnd, width, height);
}

void AsSnake::Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsSnake::Tail(HWND hWnd)
{
	body.push_back(Snake_Rect);
	entry(body.back().top, body.back().left, false);
	if (body.size() > tail_length)
		InvalidateRect(hWnd, &body.front(), FALSE);
}

void AsSnake::Head(HWND hWnd, int width, int height)
{ 
	switch (dir)
	{
	case LEFT:
		Snake_Rect.left -= AsConfig::scale;
		Snake_Rect.right -= AsConfig::scale;
		if (Snake_Rect.left < 0) {
			Snake_Rect.right = (width/ AsConfig::scale)* AsConfig::scale;
			Snake_Rect.left = Snake_Rect.right - AsConfig::scale;
		}
		break;

	case RIGHT:
		Snake_Rect.left += AsConfig::scale;
		Snake_Rect.right += AsConfig::scale;
		if (width < Snake_Rect.right) {
			Snake_Rect.right = AsConfig::scale;
			Snake_Rect.left = 0;
		}
		break;

	case UP:
		Snake_Rect.top -= AsConfig::scale;
		Snake_Rect.bottom -= AsConfig::scale;
		if (Snake_Rect.top < 0) {
			Snake_Rect.bottom = ((height - AsConfig::Functional_frame)/ AsConfig::scale) * AsConfig::scale;
			Snake_Rect.top = Snake_Rect.bottom - AsConfig::scale;
		}
		break;

	case DOWN:
		Snake_Rect.top += AsConfig::scale;
		Snake_Rect.bottom += AsConfig::scale;
		if (height < Snake_Rect.bottom + AsConfig::Functional_frame) {
			Snake_Rect.top = 0;
			Snake_Rect.bottom = AsConfig::scale;
		}
		break;

	case UNK:
		break;
	}
	Autocannibalism(Snake_Rect);
	if (Apple.Eat(Snake_Rect)) {
		++tail_length;
	}
	InvalidateRect(hWnd, &Snake_Rect, FALSE);
}

void AsSnake::Autocannibalism(RECT rect)
{
	if (!Level[rect.top / AsConfig::scale][rect.left / AsConfig::scale])
		dir = UNK;
}