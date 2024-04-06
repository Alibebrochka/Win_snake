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

void AsApple::Spawn(HWND hWnd, int width, int height, vector<vector<bool>> Level)
{
	if (width - AsConfig::Frame < Apple_Rect.left ||
		(height - AsConfig::Functional_frame - AsConfig::Frame) < Apple_Rect.top)
		does_not_have_an_apple = true;

	if (does_not_have_an_apple) {

		LONG coord_X{};
		LONG coord_Y{};
		do {
			coord_X = rand() % ((width) / AsConfig::scale) * AsConfig::scale;
			coord_Y = rand() % ((height - AsConfig::Functional_frame) / AsConfig::scale) * AsConfig::scale;
		} while (!Level[coord_Y / AsConfig::scale][coord_X / AsConfig::scale]);

		Apple_Rect.left = coord_X;
		Apple_Rect.right = coord_X + AsConfig::scale;
		Apple_Rect.top = coord_Y;
		Apple_Rect.bottom = coord_Y + AsConfig::scale;
		does_not_have_an_apple = false;
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
