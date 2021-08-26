#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "Window/window.h"

namespace GL
{
	class GRAPHICSENGINE_API BaseGame
	{
	public:
		BaseGame();
		~BaseGame();
		void Play();
	private:
		Window* window;
		Render* render;
		void Init();
		void Update();
		void DeInit();
	};
}

#endif // !BASEGAME_H