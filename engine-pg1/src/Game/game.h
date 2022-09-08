#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"

#include "Player/player.h"
#include "Camera/camera.h"
#include "Entity/Entity2D/Shape/shape.h"
#include "Entity/Entity2D/Sprite/sprite.h"
#include "Entity/Entity3D/entity3D.h"
#include "PlaneBSP/planeBSP.h"

#include "Light/DirectionalLight/directionalLight.h"
#include "Light/PointLight/pointLight.h"
#include "Light/SpotLight/spotLight.h"

#include "Importer/ModelImporter/modelImporter.h"

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

		Entity3D* girScene;
		Entity3D* objStaticMid;
		Entity3D* objStaticLeft;
		Entity3D* objStaticFront;
		Entity3D* objStaticRight;
		Entity3D* objMovable;
		Entity3D* node;

		void InitEntities();
		void InitLights();
		void UpdateInputs();
	};
}

#endif // !GAME_H
