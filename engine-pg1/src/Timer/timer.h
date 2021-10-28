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
		void Update();
		float GetDeltaTime();

	private:
		double oldTimer;
		float deltaTime;
	};
}

#endif // !TIMER_H