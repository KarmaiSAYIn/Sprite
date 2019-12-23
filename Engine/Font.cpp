#include "Font.h"
#include "RectI.h"

Font::Font(std::string filename, int nGlyphWidth, int nGlyphHeight, int nColumns, Color chroma)
	:
	FontSheet(filename),
	chroma(chroma),
	nGlyphWidth(nGlyphWidth),
	nGlyphHeight(nGlyphHeight),
	nColumns(nColumns)
{
}

void Font::Render(std::string string, const Vei2& pos, Graphics& gfx, Color color)
{
	Vei2 currPos = pos;
	for (const char c : string)
	{
		if (c == FirstChar)
		{
			currPos.x += nGlyphWidth;
			continue;
		}
		else if (c == '\n')
		{
			currPos.x = pos.x;
			currPos.y += nGlyphHeight;
			continue;
		}
		else if (c > FirstChar&& c <= LastChar)
		{
			const int glyphIndex = c - FirstChar;
			const int glyphX = glyphIndex % nColumns;
			const int glyphY = glyphIndex / nColumns;

			const RectI glyphRect = RectI(Vei2(glyphX * nGlyphWidth, glyphY * nGlyphHeight), nGlyphWidth, nGlyphHeight);
			gfx.DrawSpriteSubstitution(currPos, FontSheet, glyphRect, chroma, color);
			currPos.x += nGlyphWidth;
		}
	}
}
