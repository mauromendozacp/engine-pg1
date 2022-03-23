#include "timer.h"

namespace GL
{
	float Timer::deltaTime = 0.0f;
	double Timer::oldTimer = glfwGetTime();

	Timer::Timer()
	{
	}

	Timer::~Timer() {}

	void Timer::Update(float currentTime)
	{
		deltaTime = currentTime - oldTimer;
		oldTimer = currentTime;
	}

	float Timer::GetDeltaTime()
	{
		return deltaTime;
	}
}