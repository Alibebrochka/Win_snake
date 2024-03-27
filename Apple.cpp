#include "Apple.h"


AsApple::AsApple():scale{ 25 },
apple_col(CreateSolidBrush(RGB(255, 0, 0)))
{}
void AsApple::Ñreation(HWND hWnd, int width, int height)
{
	if (does_not_have_an_apple) {
		does_not_have_an_apple = false;
		int coord_X = 1 + rand() % (width - scale);
		int coord_Y = 1 + rand() % (height - scale - Frame_Correction);

		Apple_Rect.left = coord_X;
		Apple_Rect.right = coord_X + scale;
		Apple_Rect.top = coord_Y;
		Apple_Rect.bottom = coord_Y + scale;
	}
	InvalidateRect(hWnd, &Apple_Rect, FALSE);
}
