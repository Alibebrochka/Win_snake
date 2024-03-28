#include "Apple.h"

AsApple::AsApple():
Apple_Col_Pen(CreatePen(PS_SOLID, 0, RGB(255, 0, 0))),
Apple_Col_Brush(CreateSolidBrush(RGB(255, 0, 0)))
{}

void AsApple::Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsApple::Spawn(HWND hWnd, int width, int height)
{
	if (does_not_have_an_apple) {
		does_not_have_an_apple = false;
		int coord_X = 1 + rand() % (width - AsConfig::scale);
		int coord_Y = 1 + rand() % (height - AsConfig::scale - AsConfig::Frame_Correction);

		Apple_Rect.left = coord_X;
		Apple_Rect.right = coord_X + AsConfig::scale;
		Apple_Rect.top = coord_Y;
		Apple_Rect.bottom = coord_Y + AsConfig::scale;
	}
	InvalidateRect(hWnd, &Apple_Rect, FALSE);
}

bool AsApple::Eat(RECT snk_rek)
{
	RECT intersection_rect{};
	if (IntersectRect(&intersection_rect, &Apple_Rect, &snk_rek)) 
		does_not_have_an_apple = true;
	return does_not_have_an_apple;
}