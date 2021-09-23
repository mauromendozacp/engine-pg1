#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
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
		Render* render;
		virtual void Init();
		virtual void Update();
		virtual void DeInit();
	};	
}

#endif // !BASEGAME_H