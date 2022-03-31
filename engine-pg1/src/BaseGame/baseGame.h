#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "Camera/camera.h"
#include "Input/input.h"
#include "Timer/timer.h"
#include "LightManager/lightManager.h"
#include "Collision/collision.h"

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

		void InitEngine();
		void UpdateEngine();
		void DeInitEngine();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void DeInit() = 0;
	};	
}

#endif // !BASEGAME_H