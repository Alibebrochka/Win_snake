#include "Engine.h"

vector<vector<int>> AsEngine::Map = vector<vector<int>>(0, vector<int>(0));

void AsEngine::Init(HWND hWnd, RECT Start_Win)
{
	int width = (Start_Win.left + Start_Win.right - Editing_Window) - (Start_Win.left + Editing_Window);
	int height = (Start_Win.top + Start_Win.bottom) - (Start_Win.top + Editing_Window);

	Map = vector<vector<int>>(height / AsConfig::scale, vector<int>(width / AsConfig::scale, 1));

	Snake.Rect.left = AsConfig::Scaling(width / 2);
	Snake.Rect.right = Snake.Rect.left + AsConfig::scale;
	Snake.Rect.top = AsConfig::Scaling(height / 2);
	Snake.Rect.bottom = Snake.Rect.top + AsConfig::scale;

	Snake.body.push_back(Snake.Rect);
	
	entry(Snake.body.back().top, Snake.body.back().left, 0);

	SetTimer(hWnd, WM_USER + 1, 85, 0);
}

void AsEngine::Draw(HDC hdc, HWND hWnd)
{
	if (Apple.does_not_have_an_apple)
		Apple.Draw(hdc, AsConfig::BG_Brush, AsConfig::BG_Pen, Apple.Rect);
	else
		Apple.Draw(hdc, Apple.Color_Brush_now, Apple.Color_Pen_now, Apple.Rect);

	Snake.Draw(hdc, Snake.Color_Brush_now, Snake.Color_Pen_now, Snake.Rect);

	if (Snake.body.size() > Snake.get_tail_length()) {

		if (Map[Snake.body.front().top / AsConfig::scale][Snake.body.front().left / AsConfig::scale] != 3)
			Snake.Draw(hdc, AsConfig::BG_Brush, AsConfig::BG_Pen, Snake.body.front());

		entry(Snake.body.front().top, Snake.body.front().left, 1);
		Snake.body.pop_front();
	}
}

int AsEngine::On_Time(HWND hWnd)
{
	//перевірка на зміну розмірів вікна
	GetWindowRect(hWnd, &Win_Rect);
	int width_new = (Win_Rect.right - Editing_Window) - (Win_Rect.left + Editing_Window);
	int height_new = Win_Rect.bottom - (Win_Rect.top + Editing_Window);

	//якщо розміри не співпадають то вони оновлюються
	if (Width != width_new || Height != height_new) {
		Width = width_new;
		Height = height_new;
		//оновлення мапи
		Map.resize(Height / AsConfig::scale, vector<int>(Width, 1));
		for (auto& x : Map)
			x.resize(Width / AsConfig::scale, 1);
	}

	Apple.Spawn(hWnd, Width, Height, Map, &Snake);
	if (Snake.dir != UNK)
		Snake.Movement(hWnd, Width, Height, Snake.state, Apple);
	//Snake.port = false;
	return 0;
}

void AsEngine::entry(int rows, int columns, int b)
{
	if (Map[rows / AsConfig::scale][columns / AsConfig::scale] == 3 && b==0)
		return;
	Map[rows / AsConfig::scale][columns / AsConfig::scale] = b;
}
