#include "Animation.h"
#include "RectI.h"
#include <assert.h>

Animation::Animation(Surface& SpriteSheet, Vei2 StartingPos, int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime, Color chroma)
	:
	nFrames(nFrames),
	fFrameTime(fFrameTime),
	nSpriteWidth(nSpriteWidth),
	nSpriteHeight(nSpriteHeight),
	SpriteSheet(SpriteSheet),
	chroma(chroma)
{
	//Insures that no frames of animations can be drawn from an area outside of the sprite sheet.
	assert(RectI(StartingPos.x, StartingPos.x + nSpriteWidth * nFrames, StartingPos.y, StartingPos.y + nSpriteHeight).IsContainedBy(SpriteSheet.GetRect()));

	for (int i = 0; i < nFrames; i++)
	{
		frames.emplace_back(Vei2((i + StartingPos.x) * nSpriteWidth, StartingPos.y), nSpriteWidth, nSpriteHeight);
	}
}

int Animation::GetCurrentFrame() const
{
	return nCurrentFrame;
}

void Animation::SetFrame(int nFrame)
{
	assert(nFrame >= 0);
	assert(nFrame < nFrames);
	nCurrentFrame = nFrame;
}

void Animation::SetToStandingFrame()
{
	nCurrentFrame = 0;
}

void Animation::Update(float fElapsedTime)
{
	fFrameElapsedTime += fElapsedTime;
	while (fFrameElapsedTime >= fFrameTime)
	{
		nCurrentFrame++;
		if (nCurrentFrame >= nFrames)
		{
			nCurrentFrame = 1; //Restart animation excluding the standing part.
			fFrameElapsedTime = 0.0f;
			break;
		}
		fFrameElapsedTime -= fFrameTime;
	}
}

void Animation::Draw(Vei2 pos, Graphics& gfx) const
{
	gfx.DrawSprite(pos, SpriteSheet, frames[nCurrentFrame], chroma);
}

void Animation::Draw(Vei2 pos, Graphics& gfx, Color NonChromaSubstitution) const
{
	gfx.DrawSpriteSubstitution(pos, SpriteSheet, frames[nCurrentFrame], chroma, NonChromaSubstitution);
}

