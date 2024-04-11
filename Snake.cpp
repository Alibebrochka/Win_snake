#include "Snake.h"
#include "Engine.h"

AsSnake::AsSnake():
Color_Pen(CreatePen(PS_SOLID, 0, RGB(255, 255, 255))),
Color_Brush(CreateSolidBrush(RGB(255, 255, 255)))
{}

unsigned int AsSnake::get_tail_length() const
{
	return tail_length;
}

eDirection AsSnake::dir = DOWN;

void AsSnake::Movement(HWND hWnd, int width, int height, AsApple Apple)
{
	Tail(hWnd);
	Head(hWnd, width, height, Apple);
}

void AsSnake::Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsSnake::Tail(HWND hWnd)
{
	body.push_back(Rect);
	AsEngine::entry(body.back().top, body.back().left, false);
	if (body.size() > tail_length)
		InvalidateRect(hWnd, &body.front(), FALSE);
}

void AsSnake::Head(HWND hWnd, int width, int height, AsApple Apple)
{ 
	switch (dir)
	{
	case LEFT:
		Rect.left -= AsConfig::scale;
		Rect.right -= AsConfig::scale;
		if (Rect.left < 0) {
			Rect.right = (width/ AsConfig::scale)* AsConfig::scale;
			Rect.left = Rect.right - AsConfig::scale;
		}
		break;

	case RIGHT:
		Rect.left += AsConfig::scale;
		Rect.right += AsConfig::scale;
		if (width < Rect.right) {
			Rect.right = AsConfig::scale;
			Rect.left = 0;
		}
		break;

	case UP:
		Rect.top -= AsConfig::scale;
		Rect.bottom -= AsConfig::scale;
		if (Rect.top < 0) {
			Rect.bottom = ((height - AsConfig::Functional_frame)/ AsConfig::scale) * AsConfig::scale;
			Rect.top = Rect.bottom - AsConfig::scale;
		}
		break;

	case DOWN:
		Rect.top += AsConfig::scale;
		Rect.bottom += AsConfig::scale;
		if (height < Rect.bottom + AsConfig::Functional_frame) {
			Rect.top = 0;
			Rect.bottom = AsConfig::scale;
		}
		break;

	case UNK:
		break;
	}
	Autocannibalism(Rect);
	if (Apple.Eat(Rect)) {
		++tail_length;
	}
	InvalidateRect(hWnd, &Rect, FALSE);
}

void AsSnake::Autocannibalism(RECT rect)
{
	if (!AsEngine::Map[rect.top / AsConfig::scale][rect.left / AsConfig::scale])
		dir = UNK;

}