#pragma once
#include "Animation.h"
#include "Graphics.h"
#include "Colors.h"
#include "Vei2.h"
#include <string>

class Character
{
public:
	Character(const Vei2& StartingPos, std::string filename, Color chroma = Colors::Magenta);

	void Update();
	void Draw() const;

private:
	enum class Sequence
	{
		StandingLeft,
		StandingRight,
		StandingUp,
		StandingDown,
		WalkingLeft,
		WalkingRight,
		WalkingUp,
		WalkingDown,
	};

private:
	Sequence currSequence = Sequence::StandingUp;
	std::vector<Animation> SequenceAnimations;
};

