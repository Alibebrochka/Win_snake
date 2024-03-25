#include "ASnake.h"

AsSnake::AsSnake():scale{ 25 } ,
snake_color(CreateSolidBrush(RGB(255, 255, 255))),
black(CreateSolidBrush(RGB(0, 0, 0)))
{}

 eDirection AsSnake::dir = RIGHT;

void AsSnake::Init(HWND hWnd)
{
	GetWindowRect(hWnd, &Win_Rect);
	int width = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	Snake_Rect.left =  width / 2 ;
	Snake_Rect.right = Snake_Rect.left + scale;
	Snake_Rect.top = height / 2;
	Snake_Rect.bottom = Snake_Rect.top + scale;
	SetTimer(hWnd, WM_USER + 1, 100, 0);
}

void AsSnake::Go(HDC hdc, HWND hWnd)
{
	Draw(hdc, snake_color, Snake_Rect);

	if (body.size() > tail_length) {
		Draw(hdc, black, body.front());
		body.pop_front();
	}
}

int AsSnake::On_Time(HWND hWnd) 
{
	Movement(hWnd);
	Teleport_Head(hWnd);
	return 0;
}

void AsSnake::Draw(HDC hdc, HBRUSH hbrush, RECT rect)
{
	SelectObject(hdc, hbrush);
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
}

void AsSnake::Head()
{
	switch (dir)
	{
	case LEFT:
		Snake_Rect.left -= scale;
		Snake_Rect.right -= scale;
		break;
	case RIGHT:
		Snake_Rect.left += scale;
		Snake_Rect.right += scale;
		break;
	case UP:
		Snake_Rect.top -= scale;
		Snake_Rect.bottom -= scale;
		break;
	case DOWN:
		Snake_Rect.top += scale;
		Snake_Rect.bottom += scale;
		break;
	default:
		break;
	}
}

void AsSnake::Tail(HWND hWnd)
{
	body.push_back({ Snake_Rect.left, Snake_Rect.top, Snake_Rect.right, Snake_Rect.bottom });
	if (body.size() > tail_length)
		InvalidateRect(hWnd, &body.front(), FALSE);
}

void AsSnake::Movement(HWND hWnd)
{
	Tail(hWnd);
	Head();
}

void AsSnake::Teleport_Head(HWND hWnd)
{
	GetWindowRect(hWnd, &Win_Rect);
	int width = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height = Win_Rect.bottom - (Win_Rect.top + Editing_Window);
	//RIGHT
	if (width <= Snake_Rect.right) {
		Snake_Rect.right = 0;
		Snake_Rect.left = scale;
	}
	//DOWN
	else if (height <= Snake_Rect.bottom + 40) {
		Snake_Rect.top = 0;
		Snake_Rect.bottom = scale;
	}
	//LEFT
	else if (Snake_Rect.left <= 0) {
		Snake_Rect.right = width;
		Snake_Rect.left = width - scale;
	}
	//UP
	else if (Snake_Rect.top < 0) {
		Snake_Rect.bottom = height - 40;
		Snake_Rect.top = height - scale - 40;
	}
	InvalidateRect(hWnd, &Snake_Rect, FALSE);
}
