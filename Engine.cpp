#include "Engine.h"
vector<vector<bool>> AsEngine::Map = vector<vector<bool>>(0, vector<bool>(0));

void AsEngine::Init(HWND hWnd, RECT Start_Win)
{
	srand(static_cast<unsigned int>(time(0)));

	int width = (Start_Win.left + Start_Win.right - Editing_Window) - (Start_Win.left + Editing_Window);
	int height = (Start_Win.top + Start_Win.bottom) - (Start_Win.top + Editing_Window);

	Map = vector<vector<bool>>(height / AsConfig::scale, vector<bool>(width / AsConfig::scale, true));

	Snake.Rect.left = AsConfig::Scaling(width / 2);
	Snake.Rect.right = Snake.Rect.left + AsConfig::scale;
	Snake.Rect.top = AsConfig::Scaling(height / 2);
	Snake.Rect.bottom = Snake.Rect.top + AsConfig::scale;

	Snake.body.push_back(Snake.Rect);
	
	entry(Snake.body.back().top, Snake.body.back().left, false);

	SetTimer(hWnd, WM_USER + 1, 75, 0);
}

void AsEngine::Go(HDC hdc, HWND hWnd)
{
	if (Snake.dir == UNK) {
		;
	}
	else {
		if (Apple.does_not_have_an_apple)
			Apple.Draw(hdc, AsConfig::BG_Brush, AsConfig::BG_Pen, Apple.Rect);
		else
			Apple.Draw(hdc, Apple.Col_Brush, Apple.Col_Pen, Apple.Rect);

		Snake.Draw(hdc, Snake.Color_Brush, Snake.Color_Pen, Snake.Rect);

		if (Snake.body.size() > Snake.get_tail_length()) {
			Snake.Draw(hdc, AsConfig::BG_Brush, AsConfig::BG_Pen, Snake.body.front());
			entry(Snake.body.front().top, Snake.body.front().left, true);
			Snake.body.pop_front();
		}
	}
}

int AsEngine::On_Time(HWND hWnd)
{
	GetWindowRect(hWnd, &Win_Rect);
	int width_new = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height_new = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	if (Width != width_new || Height != height_new) {
		Width = width_new;
		Height = height_new;
		Map.resize(Height / AsConfig::scale, vector<bool>(Width, true));
		for (auto& x : Map)
			x.resize(Width / AsConfig::scale, true);
	}

	Apple.Spawn(hWnd, Width, Height, Map);
	if (Snake.dir != UNK)
		Snake.Movement(hWnd, Width, Height, Apple);
	return 0;
}

void AsEngine::entry(int rows, int columns, bool b)
{
	Map[rows / AsConfig::scale][columns / AsConfig::scale] = b;
}
