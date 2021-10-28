#include "timer.h"

namespace GL
{
	Timer::Timer()
	{
		deltaTime = 0.0f;
		oldTimer = glfwGetTime();
	}

	Timer::~Timer() {}

	void Timer::Update()
	{
		double t = glfwGetTime();
		deltaTime = (t - oldTimer) / 1000.0f;
		oldTimer = t;
	}

	float Timer::GetDeltaTime()
	{
		return deltaTime;
	}
}