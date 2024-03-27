#pragma once
#include <Windows.h>
#include <cstdlib> // для функций rand() и srand()
#include <ctime> // для функции time()
class AsApple
{
	bool does_not_have_an_apple = true;//не має яблука?

public:
	char const Frame_Correction = 51;
	int const scale{};

	HBRUSH const apple_col{};
	RECT Apple_Rect{};

	AsApple();

	void Сreation(HWND hWnd, int width, int height);
private:
};