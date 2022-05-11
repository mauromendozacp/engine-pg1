#ifndef INPUT_H
#define INPUT_H

#include "Window/window.h"
#include "Camera/camera.h"
#include "GLM/ext/matrix_transform.hpp"
#include "keycodes.h"
#include <list>

namespace GL
{
	class GRAPHICSENGINE_API Input
	{
		static Window* window;
		static Camera* camera;

		static std::list<int> currentKeysDown;
		static glm::vec2 lastPos;
		static bool firstMouse;

	public:
		Input();
		~Input();

		static void Init(Window* wind, Camera* cam);
		static void SetCamera(Camera* cam);
		static bool IsKeyPressed(int keycode);
		static bool IsKeyDown(int keycode);

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, double posX, double posY);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		
	};
}

#endif // !INPUT_H
