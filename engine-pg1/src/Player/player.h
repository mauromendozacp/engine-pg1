#ifndef PLAYER_H
#define PLAYER_H

#include "exports.h"
#include "Input/input.h"
#include "Sprite/sprite.h"

using namespace GL;

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
		Player();
		Player(Camera* camera);
		~Player();

		void Init(Render* render, float moveSpeed, float rotSpeed, const char* textureUrl);
		void Update();
		void Draw();
		void DeInit();

		Sprite* GetSprite();
		
		void SetPosition(glm::vec3 pos);
		glm::vec3 GetPosition();

	private:
		Sprite* sprite;
		Camera* camera;

		STATUS status;
		float moveSpeed;
		float rotSpeed;

		void Inputs();
		void ChangeStatus(STATUS status);
		float GetSpeedDelta();
	};
}

#endif // !PLAYER_H
