#include "animation.h"

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

	void Animation::AddFrame(float frameX, float frameY, float frameWidth, float frameHeight, float textureWidth, float textureHeight, float duration, float frameCount)
	{
		length = duration / 1000;
		float frameXIndex = 0;

		for (int i = 0; i < frameCount; i++)
		{
			Frame frame;

			frame.GetUVCords()[0].u = (frameX + frameXIndex) / textureWidth;
			frame.GetUVCords()[0].v = frameY / textureHeight;

			frame.GetUVCords()[1].u = ((frameX + frameXIndex) + frameWidth) / textureWidth;
			frame.GetUVCords()[1].v = frameY / textureHeight;

			frame.GetUVCords()[2].u = (frameX + frameXIndex) / textureWidth;
			frame.GetUVCords()[2].v = (frameY + frameHeight) / textureHeight;

			frame.GetUVCords()[3].u = ((frameX + frameXIndex) + frameWidth) / textureWidth;
			frame.GetUVCords()[3].v = (frameY + frameHeight) / textureHeight;

			frames.push_back(frame);
			frameXIndex += frameWidth;
		}
	}

	float Animation::GetCurrentFrame()
	{
		return currentFrame;
	}

	std::vector<Frame> Animation::GetFrames()
	{
		return frames;
	}
}