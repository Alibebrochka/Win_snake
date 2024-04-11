#pragma once
#include <Windows.h>
#include <list>
#include <vector>

using namespace std;

class AColor {
public:
	unsigned char R, G, B;
	AColor(unsigned char r, unsigned char g, unsigned char b);
};

class AsConfig {
public:

	static HPEN BG_Pen;
	static HBRUSH BG_Brush;

	static void Setup_Colors();
	static void Create_Pen_Brush(const AColor& color, HPEN& pen, HBRUSH& brush);
	static void Create_Pen_Brush(unsigned char r, unsigned char g, unsigned char b, HPEN& pen, HBRUSH& brush);
	static const AColor BG_Color;




	static char const Frame = 2;
	static char const Functional_frame = 51;
	static unsigned short const scale = 25;
	static int Scaling(int num);
};