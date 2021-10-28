#include "timer.h"

namespace GL
{

	Timer::Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer() {}

	float Timer::GetTimeElapsed()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration.count();
	}

}