#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"

#include "Renderer/renderer.h"
#include "Camera/camera.h"
#include "Input/input.h"
#include "Timer/timer.h"

#include "Light/LightManager/lightManager.h"
#include "Material/MaterialManager/materialManager.h"
#include "Collision/Collision2D/collision2D.h"
#include "Camera/ThirdPersonCamera/thirdPersonCamera.h"
#include "OcclusionCulling/occlusionCulling.h"

#include <stdlib.h>
#include <time.h>

namespace GL
{
	class GRAPHICSENGINE_API BaseGame
	{
	public:
		BaseGame();
		~BaseGame();
		void Play();

	protected:
		Window* window;
		Render* render;
		Camera* mainCamera;
		LightManager* lightManager;
		std::string title;
		bool terminateEngine;

		void InitEngine();
		void UpdateEngine();
		void DeInitEngine();
		void CloseEngine();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void DeInit() = 0;
	};	
}

#endif // !BASEGAME_H