#ifndef ANIMATION_H
#define ANIMATION_H

#include "exports.h"

#include "Frame/frame.h"
#include "Timer/timer.h"
#include "Importer/TextureImporter/textureImporter.h"
#include "atlasConfig.h"

#include <vector>
#include <iostream>

namespace GL
{
	class GRAPHICSENGINE_API Animation
	{
	public:
		Animation();
		~Animation();

		bool Update();
		void SetAnimation(Texture* textureData, float speed);
		void AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, int frameCount);
		void AddFrames(AtlasConfig atlas);
		int GetCurrentFrame();
		std::vector<Frame> GetFrames();

	private:
		float currentTime;
		int currentFrame;
		float speed;
		Texture* textureData;
		std::vector<Frame> frames;
	};
}

#endif // !ANIMATION_H