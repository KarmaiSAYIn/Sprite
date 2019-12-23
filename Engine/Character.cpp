#include "Character.h"
#include <assert.h>

Character::Character(const Vec2& pos, Surface& SpriteSheet, const Vei2& SpriteSheetPos,
	int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime, float fSpeed, Color chroma)
	:
	pos(pos),
	SpriteSheet(SpriteSheet),
	fSpeed(fSpeed)
{
	const int nSequences = 4;
	for (int y = 0; y < nSequences; y++)
		SequenceAnimations.emplace_back(SpriteSheet, Vei2(SpriteSheetPos.x, y * nSpriteHeight + SpriteSheetPos.y), nSpriteWidth, nSpriteHeight, nFrames, fFrameTime);
}

void Character::StopMovment()
{
	MovementState = MovementStates::Standing;
}

void Character::StartMovment()
{
	MovementState = MovementStates::Walking;
}

void Character::SetDirection(const Vei2& dir)
{
	assert(std::abs(dir.x) + std::abs(dir.y) == 1 || dir.x + dir.y == 0);

	int lastSequenceFrame = SequenceAnimations[(int)currSequence].GetCurrentFrame();
	if (dir.x > 0)
	{
		currSequence = Sequence::Right;
	}
	else if (dir.x < 0)
	{
		currSequence = Sequence::Left;
	}
	else if (dir.y > 0)
	{
		currSequence = Sequence::Up;
	}
	else if (dir.y < 0)
	{
		currSequence = Sequence::Down;
	}

	SequenceAnimations[(int)currSequence].SetFrame(lastSequenceFrame);
}

void Character::Update(const float fElapsedTime, const Vec2& delta_pos)
{
	if (MovementState == MovementStates::Standing && !(std::abs(delta_pos.x) + std::abs(delta_pos.y) > 0))
	{
		SequenceAnimations[(int)currSequence].SetToStandingFrame();
	}
	else 
	{
		SequenceAnimations[(int)currSequence].Update(fElapsedTime);
		StartMovment();
		pos += delta_pos * fElapsedTime * fSpeed; 
	}
}

void Character::Draw(Graphics& gfx) const
{
	SequenceAnimations[(int)currSequence].Draw((Vei2)pos, gfx);
}
