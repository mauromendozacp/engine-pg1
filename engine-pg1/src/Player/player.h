#ifndef PLAYER_H
#define PLAYER_H

#include "Entity/Entity3D/entity3D.h"
#include "Timer/timer.h"
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

		void Init(GL::Camera* camera, float moveSpeed, float rotSpeed);
		void Update();

	private:
		GL::Camera* camera;

		float moveBaseSpeed;
		float moveSpeed;
		float rotSpeed;

		void Inputs();
		float GetSpeedDelta();
	};
}

#endif // !PLAYER_H
