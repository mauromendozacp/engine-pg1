#ifndef GAME_H
#define GAME_H

#include "../Window/window.h"

namespace GL
{
	class BaseGame
	{
	public:
		BaseGame();
		~BaseGame();
		void Init();
		void Update();
		void Draw();
		void DeInit();
	private:
		Window* window;

		void InitLibrary();
		bool OpenWindow();
	};
}

#endif // !GAME_h