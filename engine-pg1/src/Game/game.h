#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include "Player/player.h"
#include "Camera/camera.h"
#include "Shape/shape.h"
#include "Light/light.h"
#include "Light/DirectionalLight/directionalLight.h"
#include "Light/PointLight/pointLight.h"
#include "Light/SpotLight/spotLight.h"
#include "Material/SolidMaterial/solidMaterial.h"
#include "Material/TextureMaterial/textureMaterial.h"
#include "Texture/texture.h"
#include "Entity3D/entity3D.h"
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
		Entity3D* guitarBackpack;

		SolidMaterial* defaultSolidMaterial;
		TextureMaterial* defaultTextureMaterial;

		void InitMaterial();
		void InitEntities();
		void InitLights();
	};
}

#endif // !GAME_H
