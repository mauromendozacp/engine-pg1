#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"

#include "Player/player.h"
#include "Camera/camera.h"
#include "Entity/Entity2D/Shape/shape.h"
#include "Entity/Entity3D/entity3D.h"

#include "Light/DirectionalLight/directionalLight.h"
#include "Light/PointLight/pointLight.h"
#include "Light/SpotLight/spotLight.h"

#include "Material/SolidMaterial/solidMaterial.h"
#include "Material/TextureMaterial/textureMaterial.h"

#include <iostream>

using namespace GL;

namespace GameXD
{
	int const cubesLenght = 10;

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
		Shape* cubeLight[cubesLenght];
		Shape* spotCubeLight;
		Sprite* tnt;
		Entity3D* guitarBackpack1;

		SolidMaterial* defaultSolidMaterial;
		TextureMaterial* defaultTextureMaterial;

		void InitMaterial();
		void InitEntities();
		void InitLights();
		void UpdateInputs();
	};
}

#endif // !GAME_H
