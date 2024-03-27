#include "Snake.h"

AsSnake::AsSnake():
snake_color(CreateSolidBrush(RGB(255, 255, 255))),
black(CreateSolidBrush(RGB(0, 0, 0)))
{}

 eDirection AsSnake::dir = RIGHT;

void AsSnake::Init(HWND hWnd)
{
	srand(static_cast<unsigned int>(time(0)));
	GetWindowRect(hWnd, &Win_Rect);
	int width = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	Snake_Rect.left =  width / 2 ;
	Snake_Rect.right = Snake_Rect.left + Apple.scale;
	Snake_Rect.top = height / 2;
	Snake_Rect.bottom = Snake_Rect.top + Apple.scale;
	SetTimer(hWnd, WM_USER + 1, 100, 0);
}

void AsSnake::Go(HDC hdc, HWND hWnd)
{
	Draw(hdc, Apple.apple_col, Apple.Apple_Rect);
	Draw(hdc, snake_color, Snake_Rect);

	if (body.size() > tail_length) {
		Draw(hdc, black, body.front());
		body.pop_front();
	}
}

int AsSnake::On_Time(HWND hWnd) 
{
	GetWindowRect(hWnd, &Win_Rect);
	int width = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height = Win_Rect.bottom - (Win_Rect.top + Editing_Window);
	Movement(hWnd, width, height);
	Apple.Ñreation(hWnd, width, height);
	return 0;
}

void AsSnake::Movement(HWND hWnd, int width, int height)
{
	Tail(hWnd);
	Head();
	Teleport_Head(hWnd, width, height);
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
		Snake_Rect.left -= Apple.scale;
		Snake_Rect.right -= Apple.scale;
		break;
	case RIGHT:
		Snake_Rect.left += Apple.scale;
		Snake_Rect.right += Apple.scale;
		break;
	case UP:
		Snake_Rect.top -= Apple.scale;
		Snake_Rect.bottom -= Apple.scale;
		break;
	case DOWN:
		Snake_Rect.top += Apple.scale;
		Snake_Rect.bottom += Apple.scale;
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

void AsSnake::Teleport_Head(HWND hWnd, int width, int height)
{ 
	//RIGHT
	if (width < Snake_Rect.right) {
		Snake_Rect.right = 0;
		Snake_Rect.left = Apple.scale;
	}
	//DOWN
	else if (height < Snake_Rect.top + Apple.Frame_Correction) {
		Snake_Rect.top = 0;
		Snake_Rect.bottom = Apple.scale;
	}
	//LEFT
	else if (Snake_Rect.right < 0) {
		Snake_Rect.right = width;
		Snake_Rect.left = width - Apple.scale;
	}
	//UP
	else if (Snake_Rect.bottom < 0) {
		Snake_Rect.bottom = height - Apple.Frame_Correction;
		Snake_Rect.top = height - Apple.scale - Apple.Frame_Correction;
	}
	InvalidateRect(hWnd, &Snake_Rect, FALSE);
}
