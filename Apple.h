#pragma once
#include <Windows.h>
#include <cstdlib> // ��� ������� rand() � srand()
#include <ctime> // ��� ������� time()
class AsApple
{
	bool does_not_have_an_apple = true;//�� �� ������?

public:
	char const Frame_Correction = 51;
	int const scale{};

	HBRUSH const apple_col{};
	RECT Apple_Rect{};

	AsApple();

	void �reation(HWND hWnd, int width, int height);
private:
};