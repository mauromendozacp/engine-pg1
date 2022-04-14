#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include "Player/player.h"
#include "Camera/camera.h"
#include "Camera/FirstPersonCamera/firstPersonCamera.h"
#include "Camera/ThirdPersonCamera/thirdPersonCamera.h"
#include "Shape/shape.h"
#include "Light/light.h"
#include "Light/DirectionalLight/directionalLight.h"
#include "Light/PointLight/pointLight.h"
#include "Light/SpotLight/spotLight.h"
#include <iostream>

using namespace GL;

namespace GameXD
{
	class GRAPHICSENGINE_API Game : public BaseGame
	{
	public:
		Game();
		~Game();

	protected:
		void Init() override;
		void Update() override;
		void Draw() override;
		void DeInit() override;

	private:
		Player* player;
		Sprite* floor;
		Shape* cubeLight;
		Shape* spotCubeLight;
		Sprite* tnt;
	};
}

#endif // !GAME_H
