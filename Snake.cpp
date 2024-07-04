#include "Snake.h"
#include "Engine.h"

AsSnake::AsSnake():
Color_Pen_life(CreatePen(PS_SOLID, 0, RGB(255, 255, 255))),
Color_Brush_life(CreateSolidBrush(RGB(255, 255, 255))),
Color_Pen_dead(CreatePen(PS_SOLID, 0, RGB(255, 0, 0))),
Color_Brush_dead(CreateSolidBrush(RGB(255, 0, 0))),
Color_Pen_now(Color_Pen_life),
Color_Brush_now(Color_Brush_life)
{}

unsigned int AsSnake::get_tail_length() const
{
	return tail_length;
}

eDirection AsSnake::dir = DOWN;
eState AsSnake::state = LIFE;

void AsSnake::Movement(HWND hWnd, int width, int height, eState state, AsApple &Apple)
{
	switch (state)
	{
	case LIFE:
		Tail(hWnd);
		Head(hWnd, width, height, Apple);
		break;

	case DEAD:
		Tail(hWnd);
		Head(hWnd, width, height, Apple);
		break;

	case GAMEOVER:
		dir = UNK;
		break;

	default:
		break;
	}
	
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

void AsSnake::Head(HWND hWnd, int width, int height, AsApple &Apple)
{//нові координати голови
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
	//передаю голову
	Autocannibalism(Rect);

	if (Apple.Eat(Rect)) 
		++tail_length;
	InvalidateRect(hWnd, &Rect, FALSE);
}

void AsSnake::Autocannibalism(RECT rect)
{
	//якщо в точці переносу голови є тіло (0) то змійка врізається в ньго і помирає 
	if (!AsEngine::Map[rect.top / AsConfig::scale][rect.left / AsConfig::scale]) {
		if (state == LIFE) {
			state = DEAD;
			Color_Pen_now = Color_Pen_dead;
			Color_Brush_now = Color_Brush_dead;
		}
		else {
			state = LIFE;
			Color_Pen_now = Color_Pen_life;
			Color_Brush_now = Color_Brush_life;
		}
	}

}