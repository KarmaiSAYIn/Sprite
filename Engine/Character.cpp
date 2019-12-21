#include "Character.h"
#include <assert.h>

Character::Character(const Vec2& pos, Surface& SpriteSheet, const Vei2& SpriteSheetPos,
	int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime, Color chroma)
	:
	pos(pos),
	SpriteSheet(SpriteSheet)
{
	const int nSequences = 4;
	for (int y = 0; y < nSequences; y++)
		SequenceAnimations.emplace_back(SpriteSheet, Vei2(SpriteSheetPos.x, y * nSpriteHeight), nSpriteWidth, nSpriteHeight, nFrames, fFrameTime);
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
}

void Character::Update(const float fElapsedTime, const Vec2& delta_pos)
{
	if (MovementState != MovementStates::Standing || std::abs(delta_pos.x) + std::abs(delta_pos.y) > 0)
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
