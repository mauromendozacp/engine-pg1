#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
#include "Window/window.h"
#include "Renderer/renderer.h"

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
		

		void Init();
		void Update();
		void DeInit();
	};
}

#endif // !BASEGAME_H