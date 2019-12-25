#pragma once
#include "Colors.h"
#include "RectI.h"
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
	RectI GetRect() const;

	void PutPixel(int x, int y, Color c) const;

private:
	void LoadBmpImage(std::ifstream& in);
	void LoadPngImage(std::ifstream& in);

private:
	struct PNG
	{
		int64_t signature = 727905341920923785;
		static int64_t GetSignature() { return 727905341920923785; }
		struct IHDR
		{
			int32_t FieldSize;
			int32_t TypeCode = 1380206665;
			static int32_t GetTypeCode() { return 1380206665; }
			int32_t width;
			int32_t height;
			int8_t BitDepth;
			int8_t ColorType;
			int8_t CompressionMehtod;
			int8_t FilterMethod;
			int8_t InterlaceMethod;
			int32_t CRC;
		} ImageHeader;
	};

private:
	int width = -1;
	int height = -1;
	Color* pPixels = nullptr;
};

