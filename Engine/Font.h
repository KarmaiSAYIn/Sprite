#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Colors.h"
#include "Vei2.h"
#include <string>

class Font
{
public:
	Font(std::string filename, int GlyphWidth, int GlyphHeight, int nColumns, Color chroma = Colors::White);

	void Render(std::string string, const Vei2& pos, Graphics& gfx, Color color);

private:
	Surface FontSheet;
	Color chroma;

	const int nColumns;
	const int nGlyphWidth;
	const int nGlyphHeight;

	char FirstChar = ' ';
	char LastChar = '~';
};

