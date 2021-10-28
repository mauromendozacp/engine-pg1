#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <thread>
#include <chrono>

#include "exports.h"

namespace GL
{
	
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	struct Timer
	{
		Timer();
		~Timer();
		float GetTimeElapsed();
	};

}

#endif // !FRAME_H