#include "Animation.h"
#include "RectI.h"
#include <assert.h>

Animation::Animation(Surface& SpriteSheet, Vei2 StartingPos, int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime)
	:
	nFrames(nFrames),
	fFrameTime(fFrameTime),
	nSpriteWidth(nSpriteWidth),
	nSpriteHeight(nSpriteHeight),
	SpriteSheet(SpriteSheet)
{
	//Insures that no frames of animations can be drawn from an area outside of the sprite sheet.
	assert(RectI(StartingPos.x, StartingPos.x + nSpriteWidth * nFrames, StartingPos.y, StartingPos.y + nSpriteHeight).IsContainedBy(SpriteSheet.GetRect()));

	for (int i = 0; i < nFrames; i++)
	{
		frames.emplace_back(Vei2((i + StartingPos.x) * nSpriteWidth, StartingPos.y), nSpriteWidth, nSpriteHeight);
	}
}

void Animation::Update(float fElapsedTime)
{
	fFrameElapsedTime += fElapsedTime;
	while (fFrameElapsedTime >= fFrameTime)
	{
		nCurrentFrame++;
		if (nCurrentFrame >= nFrames)
		{
			nCurrentFrame = 0;
			break;
		}
		fFrameElapsedTime -= fFrameTime;
	}
}

void Animation::Draw(Vei2 pos, Graphics& gfx)
{
	gfx.DrawSprite(pos, SpriteSheet, frames[nCurrentFrame]);
}

