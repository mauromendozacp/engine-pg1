#ifndef PLAYER_H
#define PLAYER_H

#include "exports.h"
#include "Input/input.h"
#include "Sprite/sprite.h"
#include "Camera/FirstPersonCamera/firstPersonCamera.h"
#include "Camera/ThirdPersonCamera/thirdPersonCamera.h"

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

		void Init(Render* render, Material* material, float moveSpeed, float rotSpeed, const char* textureUrl);
		void Update();
		void Draw();
		void DeInit();

		void SetCamera(Render* render, Window* window, CAMERA_TYPE cameraType);
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
