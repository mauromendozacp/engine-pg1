#ifndef ANIMATION_H
#define ANIMATION_H

#include "exports.h"
#include "Frame/frame.h"
#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Animation
	{
	public:
		Animation();
		~Animation();

		void Update(float timer);
		void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, 
			float textureWidth, float textureHeight, float duration, int frameCount);
		int GetCurrentFrame();
		std::vector<Frame> GetFrames();

	private:
		float currentTime;
		int currentFrame;
		float length;
		std::vector<Frame> frames;
	};
}

#endif // !ANIMATION_H