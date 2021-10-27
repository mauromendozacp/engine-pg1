#include "animation.h"
#include <iostream>

namespace GL
{
	Animation::Animation()
	{
		currentTime = 0;
		currentFrame = 0;
		length = 1000;
		frames = std::vector<Frame>();
	}

	Animation::~Animation()
	{
		frames.clear();
	}

	void Animation::Update(float timer)
	{
		currentTime += timer;
		while (currentTime > length)
		{
			currentTime -= length;
		}

		float frameLength = length / frames.size();
		currentFrame = static_cast<int>(currentTime / frameLength);
	}

	void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float duration, int frameCount)
	{
		length = duration / 1000;
		float frameXIndex = 0;

		for (int i = 0; i < frameCount; i++)
		{
			Frame frame;

			frame.GetUVCords()[0].u = (frameWidth * (frameX + 1)) / textureWidth;
			frame.GetUVCords()[0].v = (frameHeight / textureHeight) * frameY;

			frame.GetUVCords()[1].u = (frameWidth * (frameX + 1)) / textureWidth;
			frame.GetUVCords()[1].v = (frameHeight / textureHeight) * (frameY - 1);

			frame.GetUVCords()[2].u = (frameWidth * frameX) / textureWidth;
			frame.GetUVCords()[2].v = (frameHeight / textureHeight) * (frameY - 1);

			frame.GetUVCords()[3].u = (frameWidth * frameX) / textureWidth;
			frame.GetUVCords()[3].v = (frameHeight / textureHeight) * frameY;

			frames.push_back(frame);
			frameXIndex += frameWidth;
		}
	}

	int Animation::GetCurrentFrame()
	{
		return currentFrame;
	}

	std::vector<Frame> Animation::GetFrames()
	{
		return frames;
	}
}