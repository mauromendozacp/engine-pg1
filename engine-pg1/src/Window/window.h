#ifndef WINDOW_H
#define WINDOW_H

#include "exports.h"
#include <iostream>

namespace GL
{
	class GRAPHICSENGINE_API Window
	{
	public:
		Window(float width, float height, std::string title);
		~Window();
		GLFWwindow* GetWindow();
		bool OpenWindow();
		void CloseWindow();
		void DestroyWindow();
	private:
		GLFWwindow* glfWindow;
		float height;
		float width;
		std::string title;
	};
}

#endif