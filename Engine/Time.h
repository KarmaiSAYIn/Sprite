#pragma once
#include <chrono>

class Time
{
public:
	Time();

	float Mark();

private:
	std::chrono::steady_clock::time_point start;
};

