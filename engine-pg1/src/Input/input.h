#ifndef INPUT_H
#define INPUT_H

#include "Window/window.h"
#include <list>

namespace GL
{
	class GRAPHICSENGINE_API Input
	{
	public:
		Input(Window* window);
		~Input();
		void Init();
		bool IsKeyPressed(int keycode, Window* window);
		bool IsKeyDown(int keycode, Window* window);
	private:
		Window* window;
	};
}

#endif // !INPUT_H
