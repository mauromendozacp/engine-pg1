#ifndef TIMER_H
#define TIMER_H

#include "exports.h"

namespace GL
{
	class GRAPHICSENGINE_API Timer
	{
	public:
		Timer();
		~Timer();

		static void Update(float currentTime);
		static float GetDeltaTime();

	private:
		static double oldTimer;
		static float deltaTime;
	};
}

#endif // !TIMER_H