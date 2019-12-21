#include "Time.h"

Time::Time()
	:
	start(std::chrono::steady_clock::now())
{
}

float Time::Mark()
{
	auto old = start;
	start = std::chrono::steady_clock::now();
	std::chrono::duration<float> duration = start - old;
	return duration.count();
}
