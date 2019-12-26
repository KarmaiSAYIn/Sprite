#include "Surface.h"
#include "ChiliWin.h"
#include "Windows.h"
#include <fstream>
#include <assert.h>
#include <algorithm>


Surface::Surface(std::string filename)
{
	std::ifstream in(filename, std::ios::binary);

	//Find file format.
	BITMAPFILEHEADER bmpFileH;
	PNG png;
	in.read(reinterpret_cast<char*>(&bmpFileH), sizeof(bmpFileH));
	in.seekg(0);
	in.read(reinterpret_cast<char*>(&png.signature), sizeof(png.signature));
	in.seekg(0);

	assert(bmpFileH.bfType == 19778 || png.signature == PNG::GetSignature());
	if (bmpFileH.bfType == 19778)
	{
		//File format is BMP.
		LoadBmpImage(in);
	}
	else if (png.signature == PNG::GetSignature())
	{
		//File format is PNG.
		LoadPngImage(in);
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

void Surface::LoadBmpImage(std::ifstream& in)
{
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

auto ReverseFourBytes(int32_t& pReverseInt, int size = sizeof(int32_t))
{
	char* pStart = reinterpret_cast<char*>(&pReverseInt);
	char* pEnd = pStart + size;
	std::reverse(pStart, pEnd); 
}

void Surface::LoadPngImage(std::ifstream& in)
{
	PNG png;

	in.read(reinterpret_cast<char*>(&png), sizeof(png));
	ReverseFourBytes(png.ImageHeader.FieldSize);
	ReverseFourBytes(png.ImageHeader.width);
	ReverseFourBytes(png.ImageHeader.height);

	assert(png.signature == PNG::GetSignature());
	assert(png.ImageHeader.TypeCode == PNG::IHDR::GetTypeCode());
	assert(png.ImageHeader.CompressionMethod == 0);
	assert(png.ImageHeader.FilterMethod == 0);
	assert(png.ImageHeader.InterlaceMethod == 0); //not supporting Adam7.

	width = png.ImageHeader.width;
	height = png.ImageHeader.height;

	std::string s;
	while (in)
	{
		s += in.get();
	}
	int IDAToffset = s.find("IDAT");
	assert(IDAToffset != std::string::npos);
	in.seekg(0, IDAToffset - 4);

	pPixels = new Color[width * height];

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (png.ImageHeader.ColorType)
			{
			case 0:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 6:
				break;
			}
		}
	}
}
