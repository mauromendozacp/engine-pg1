#ifndef INPUT_H
#define INPUT_H

#include "Window/window.h"
#include "../glm/ext/matrix_transform.hpp"
#include "keycodes.h"
#include <list>

namespace GL
{
	class GRAPHICSENGINE_API Input
	{
	public:
		Input(Window* window);
		~Input();
		void Init();
		bool IsKeyPressed(int keycode);
		bool IsKeyDown(int keycode);

		glm::vec2 GetLastPosition();
		glm::vec2 GetOffsetPosition();
		void SetOffsetPosition(glm::vec2 offsetPos);

	private:
		Window* window;
	};
}

#endif // !INPUT_H
