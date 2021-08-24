#ifndef ELEMENT_WINDOW
#define ELEMENT_WIDNOW

#include <GLFW/glfw3.h>

namespace GL
{
	class Window
	{
	public:
		int height;
		int width;
		int title;
		void OpenWindow(GLFWmonitor* monitor, GLFWwindow* share);
		void CloseWindow();
		GLFWwindow* getGLFWWindow();
	};
}

#endif