#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
#include "Shape/shape.h"
#include "Sprite/sprite.h"
#include "Renderer/renderer.h"
#include "Input/input.h"
#include "Timer/timer.h"
#include "Collision/collision.h"

namespace GL
{
	class GRAPHICSENGINE_API BaseGame
	{
	public:
		BaseGame();
		~BaseGame();

	protected:
		Window* window;
		Render* render;
		Input* input;
		Timer* timer;
		std::string title;

		void InitBase();
		void UpdateBase();
		void DeInitBase();

		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void DeInit() = 0;
	};	
}

#endif // !BASEGAME_H