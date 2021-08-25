#include "window.h"

namespace GL
{
	Window::Window(int height, int width, const char* title)
	{
		this->glfWindow = nullptr;
		this->height = height;
		this->width = width;
		this->title = title;
	}

	Window::~Window()
	{
		delete glfWindow;
	}

	GLFWwindow* Window::GetWindow()
	{
		return glfWindow;
	}

	bool Window::OpenWindow()
	{
		glfWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (glfWindow)
		{
			glfwTerminate();
			return false;
		}
		return true;
	}

	void Window::CloseWindow()
	{

	}
}