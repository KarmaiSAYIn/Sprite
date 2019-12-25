#pragma once
#include "Animation.h"
#include "Graphics.h"
#include "Colors.h"
#include "Vei2.h"
#include "Vec2.h"
#include "Surface.h"
#include <string>

class Character
{
public:
	Character(const Vec2& pos, Surface& SpriteSheet, const Vei2& SpriteSheetPos,
		int nSpriteWidth, int nSpriteHeight, int nFrames, float fFrameTime, float fSpeed, Color chroma = Colors::Magenta);

	void StopMovment();
	void StartMovment();
	void SetDirection(const Vei2& dir);
	void ActivateDamageIndicator();
	void Update(const float fElapsedTime, const Vec2& delta_pos);
	void Draw(Graphics& gfx) const;

private:
	enum class Sequence
	{
		Left,
		Right,
		Up,
		Down,
	};

	enum class MovementStates
	{
		Standing,
		Walking,
	};

private:
	MovementStates MovementState = MovementStates::Walking;
	Vec2 pos;
	Surface& SpriteSheet;
	Sequence currSequence = Sequence::Left;
	std::vector<Animation> SequenceAnimations;

	float fSpeed = -1.0f;
	float fDamageIndicatorElapsedTime = 0.0f;
	static constexpr float fDamageIndicatorTime = 0.5f;
	bool bDamageIndicatorActive = false;
};

