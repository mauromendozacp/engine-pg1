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

		float GetHeight();
		float GetWidth();
	private:

		GLFWwindow* glfWindow;
		std::string title;

		float height;
		float width;
	};
}

#endif