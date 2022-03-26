#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include "Player/player.h"
#include "Camera/camera.h"
#include "Shape/shape.h"
#include "Light/light.h"
#include "DirectionalLight/directionalLight.h"
#include "PointLight/pointLight.h"
#include "SpotLight/spotLight.h"
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

		Light* globalLight;
		DirectionalLight* directionalLight;
		PointLight* pointLight;
		SpotLight* spotLight;
	};
}

#endif // !GAME_H
