#ifndef WINDOW_H
#define WINDOW_H

#include "exports.h"
#include "../lib/GLFW/include/GLFW/glfw3.h"
#include <iostream>

namespace GL
{
	class GRAPHICSENGINE_API Window
	{
	public:
		Window(int height, int width, const char* title);
		~Window();
		GLFWwindow* GetWindow();
		bool OpenWindow();
		void CloseWindow();
	private:
		GLFWwindow* glfWindow;
		int height;
		int width;
		std::string title;
	};
}

#endif