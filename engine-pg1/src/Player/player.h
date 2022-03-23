#ifndef PLAYER_H
#define PLAYER_H

#include "exports.h"
#include "Input/input.h"
#include "Sprite/sprite.h"
#include "Camera/camera.h"

namespace GameXD
{
	enum class STATUS
	{
		IDLE,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

	class GRAPHICSENGINE_API Player
	{
	public:
		Player(GL::Camera* camera, GL::Input* input, GL::Timer* timer);
		~Player();

		void Init(GL::Render* render, float moveSpeed, float rotSpeed, const char* textureUrl);
		void Update();
		void Draw();
		void DeInit();

		GL::Sprite* GetSprite();
		glm::vec3 GetPos();

	private:
		GL::Sprite* sprite;
		GL::Camera* camera;
		GL::Input* input;
		GL::Timer* timer;

		STATUS status;
		float moveSpeed;
		float rotSpeed;

		void Inputs();
		void ChangeStatus(STATUS status);
		float GetSpeedDelta();
	};
}

#endif // !PLAYER_H
