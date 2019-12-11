#pragma once
#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface() = delete;
	Surface(std::string filename);
	Surface(const Surface& CopySurface);
	~Surface();

	Surface& operator=(const Surface& CopySurface);

	int GetWidth() const;
	int GetHeight() const;
	Color GetPixel(int x, int y) const;

	void PutPixel(int x, int y, Color c) const;

private:
	int width = -1;
	int height = -1;
	Color* pPixels = nullptr;
};

