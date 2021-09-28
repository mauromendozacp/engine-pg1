#ifndef BASEGAME_H
#define BASEGAME_H

#include "exports.h"
#include "Entity/entity.h"

namespace GL
{
	class Render;
	class Window;

	class GRAPHICSENGINE_API BaseGame
	{
	public:
		BaseGame();
		~BaseGame();
	protected:
		Window* window;
		Render* render;
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void DeInit() = 0;
	};	
}

#endif // !BASEGAME_H