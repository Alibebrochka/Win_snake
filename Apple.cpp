#include "Apple.h"

const HPEN AsApple::Color_Pen_normal(CreatePen(PS_SOLID, 0, RGB(255, 0, 0)));
const HBRUSH AsApple::Color_Brush_normal(CreateSolidBrush(RGB(255, 0, 0)));

const HPEN AsApple::Color_Pen_in_hell(CreatePen(PS_SOLID, 0, RGB(253, 255, 0)));
const HBRUSH AsApple::Color_Brush_in_hell(CreateSolidBrush(RGB(240, 90, 8)));

HPEN AsApple::Color_Pen_now = { Color_Pen_normal };
HBRUSH AsApple::Color_Brush_now = { Color_Brush_normal };

AsApple::AsApple()
{}

void AsApple::Draw(HDC hdc, HBRUSH brush, HPEN pen, RECT rect)
{
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsApple::Spawn(HWND hWnd, int width, int height, vector<vector<int>> Map, AsHell* Hell)
{
	if (true)
		Hell->Port();
	//якщо яблуко за рамками вікна то його не має
	if (width - AsConfig::Frame < Rect.right ||(height - AsConfig::Functional_frame - AsConfig::Frame) < Rect.bottom)
		does_not_have_an_apple = true;
	//спавн яблука
	if (does_not_have_an_apple) {

		LONG coord_X{};
		LONG coord_Y{};
		do {
			coord_X = AsConfig::Scaling(rand() % width - AsConfig::scale);
			coord_Y = AsConfig::Scaling(rand() % (height - AsConfig::Functional_frame - AsConfig::scale));
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
	if (IntersectRect(&intersection_rect, &Rect, &snk_rek))
		does_not_have_an_apple = true;	
	return does_not_have_an_apple;
}

void AsApple::In_Hell()
{
	Color_Pen_now = Color_Pen_in_hell;
	Color_Brush_now = Color_Brush_in_hell;
}
