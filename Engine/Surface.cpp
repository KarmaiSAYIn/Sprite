#include "Surface.h"
#include "ChiliWin.h"
#include "Windows.h"
#include <fstream>
#include <assert.h>


Surface::Surface(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);
	BITMAPFILEHEADER bmpFileH;
	BITMAPINFOHEADER bmpInfoH;

	in.read(reinterpret_cast<char*>(&bmpFileH), sizeof(bmpFileH));
	in.read(reinterpret_cast<char*>(&bmpInfoH), sizeof(bmpInfoH));

	assert(bmpInfoH.biBitCount == 24 || bmpInfoH.biBitCount == 32);
	assert(bmpInfoH.biCompression == BI_RGB);

	width = bmpInfoH.biWidth;
	height = bmpInfoH.biHeight;

	int yStart, yEnd, yDelta;
	if (height < 0)
	{
		height *= -1;
		yStart = 0;
		yEnd = height;
		yDelta = 1;
	}
	else
	{
		yStart = height - 1;
		yEnd = -1;
		yDelta = -1;
	}

	pPixels = new Color[width * height];

	in.seekg(bmpFileH.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;
	for (int y = yStart; y != yEnd; y += yDelta)
	{
		for (int x = 0; x < width; x++)
		{
			Color c;
			if (bmpInfoH.biBitCount == 32)
				c = Color(in.get(), in.get(), in.get(), in.get());
			else
				c = Color(in.get(), in.get(), in.get());

			PutPixel(x, y, c);
		}
		in.seekg(padding, std::ios::cur);
	}
}

Surface::Surface(const Surface& CopySurface)
{
	*this = CopySurface;
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface& Surface::operator=(const Surface& CopySurface)
{
	width = CopySurface.GetWidth();
	height = CopySurface.GetHeight();

	delete[] pPixels;
	pPixels = new Color[width * height];

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			PutPixel(x, y, CopySurface.GetPixel(x, y));
		}
	}

	return *this;
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

Color Surface::GetPixel(int x, int y) const
{
	return pPixels[y * width + x];
}

RectI Surface::GetRect() const
{
	return RectI(0, width, 0, height);
}

void Surface::PutPixel(int x, int y, Color c) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}
