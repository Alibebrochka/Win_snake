#include "Snake.h"

AsSnake::AsSnake():
Snake_Color_Pen(CreatePen(PS_SOLID, 0, RGB(255, 255, 255))),
Snake_Color_Brush(CreateSolidBrush(RGB(255, 255, 255))),
BG_Pen(CreatePen(PS_SOLID, 0, RGB(0, 0, 0))),
BG_Brush(CreateSolidBrush(RGB(0, 0, 0)))
{}

 eDirection AsSnake::dir = RIGHT;

void AsSnake::Init(HWND hWnd, RECT Start_Win)
{
	srand(static_cast<unsigned int>(time(0)));
	int width = (Start_Win.left + Start_Win.right - Editing_Window) - (Start_Win.left + Editing_Window);
	int height = (Start_Win.top + Start_Win.bottom) - (Start_Win.top + Editing_Window);

	Snake_Rect.left = width / 2 - AsConfig::scale;
	Snake_Rect.right = Snake_Rect.left + AsConfig::scale;
	Snake_Rect.top = height / 2 - AsConfig::scale;
	Snake_Rect.bottom = Snake_Rect.top + AsConfig::scale;
	SetTimer(hWnd, WM_USER + 1, 75, 0);
}

void AsSnake::Go(HDC hdc, HWND hWnd)
{
	if (Apple.does_not_have_an_apple)
		Apple.Draw(hdc, BG_Brush, BG_Pen, Apple.Apple_Rect);
	else
		Apple.Draw(hdc, Apple.Apple_Col_Brush,Apple.Apple_Col_Pen, Apple.Apple_Rect);

	Draw(hdc, Snake_Color_Brush, Snake_Color_Pen, Snake_Rect);

	if (body.size() > tail_length) {
		Draw(hdc, BG_Brush, BG_Pen, body.front());
		body.pop_front();
	}
}

int AsSnake::On_Time(HWND hWnd) 
{
	GetWindowRect(hWnd, &Win_Rect);
	int width = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	Apple.Spawn(hWnd, width, height, body);
	Movement(hWnd, width, height);
	return 0;
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
	body.push_back({ Snake_Rect.left, Snake_Rect.top, Snake_Rect.right, Snake_Rect.bottom });
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
		if (Snake_Rect.right < 0) {
			Snake_Rect.right = width;
			Snake_Rect.left = width - AsConfig::scale;
		}
		break;

	case RIGHT:
		Snake_Rect.left += AsConfig::scale;
		Snake_Rect.right += AsConfig::scale;
		if (width < Snake_Rect.left) {
			Snake_Rect.right = AsConfig::scale;
			Snake_Rect.left = 0;
		}
		break;

	case UP:
		Snake_Rect.top -= AsConfig::scale;
		Snake_Rect.bottom -= AsConfig::scale;
		if (Snake_Rect.bottom < 0) {
			Snake_Rect.bottom = height - AsConfig::Functional_frame;
			Snake_Rect.top = height - AsConfig::scale - AsConfig::Functional_frame;
		}
		break;

	case DOWN:
		Snake_Rect.top += AsConfig::scale;
		Snake_Rect.bottom += AsConfig::scale;
		if (height < Snake_Rect.top + AsConfig::Functional_frame) {
			Snake_Rect.top = 0;
			Snake_Rect.bottom = AsConfig::scale;
		}
		break;

	default:
		break;
	}
	if (Apple.Eat(Snake_Rect)) {
		++tail_length;
	}
	InvalidateRect(hWnd, &Snake_Rect, FALSE);
}
