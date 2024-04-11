#include "Apple.h"

AsApple::AsApple():
Col_Pen(CreatePen(PS_SOLID, 0, RGB(255, 0, 0))),
Col_Brush(CreateSolidBrush(RGB(255, 0, 0)))
{}

void AsApple::Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsApple::Spawn(HWND hWnd, int width, int height, vector<vector<bool>> Map)
{
	//якщо яблуко за рамками вікна то його не має
	if (width - AsConfig::Frame < Rect.left ||(height - AsConfig::Functional_frame - AsConfig::Frame) < Rect.top)
		does_not_have_an_apple = true;
	//спавн яблука
	if (does_not_have_an_apple) {

		LONG coord_X{};
		LONG coord_Y{};
		do {
			coord_X = AsConfig::Scaling(rand() % width);
			coord_Y = AsConfig::Scaling(rand() % (height - AsConfig::Functional_frame));
		} while (!Map[coord_Y / AsConfig::scale][coord_X / AsConfig::scale]);

		Rect.left = coord_X;
		Rect.right = coord_X + AsConfig::scale;
		Rect.top = coord_Y;
		Rect.bottom = coord_Y + AsConfig::scale;
		does_not_have_an_apple = false;
	}
	InvalidateRect(hWnd, &Rect, FALSE);
}

bool AsApple::Eat(RECT snk_rek)
{//обчислення координат пересікання прямокутників: голови і яблука
	RECT intersection_rect{};
	if (IntersectRect(&intersection_rect, &Rect, &snk_rek)) {
		does_not_have_an_apple = true;
	}
	return does_not_have_an_apple;
}
