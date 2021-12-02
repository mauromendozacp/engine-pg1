#include "timer.h"

namespace GL
{
	Timer::Timer()
	{
		oldTimer = glfwGetTime();
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
	float Timer::deltaTime = 0.0f;
}