#ifndef PLAYER_H
#define PLAYER_H

#include "Entity/Entity3D/entity3D.h"

#include "Camera/FirstPersonCamera/firstPersonCamera.h"
#include "Camera/ThirdPersonCamera/thirdPersonCamera.h"

#include "Input/input.h"

using namespace GL;

namespace GameXD
{
	class GRAPHICSENGINE_API Player : public Entity3D
	{
	public:
		Player();
		Player(Render* render);
		~Player();

		void Init(float moveSpeed, float rotSpeed);
		void Update();

		Camera* GetCamera();
		void SetCamera(Window* window, CAMERA_TYPE cameraType);

	private:
		Camera* camera;

		float moveSpeed;
		float rotSpeed;

		void Inputs();
		float GetSpeedDelta();
	};
}

#endif // !PLAYER_H
