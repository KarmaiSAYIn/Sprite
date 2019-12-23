#pragma once
#include "Surface.h"
#include "Graphics.h"
#include "Vei2.h"
#include <string>
#include <vector>

class Animation
{
public:
	Animation() = delete;
	Animation(Surface& SpriteSheet, Vei2 StartingPos, int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime, Color chroma = Colors::Magenta);

	int GetCurrentFrame() const;

	void SetFrame(int nFrame);
	void SetToStandingFrame();
	void Update(float fElapsedTime);
	void Draw(Vei2 pos, Graphics& gfx) const;

private:
	Surface& SpriteSheet;
	const int nSpriteWidth = -1;
	const int nSpriteHeight = -1;

	std::vector<RectI> frames;
	Color chroma;

	int nCurrentFrame = 0;
	const int nFrames = -1;
	float fFrameElapsedTime = 0.0f;
	const float fFrameTime = -1.0f;
};
