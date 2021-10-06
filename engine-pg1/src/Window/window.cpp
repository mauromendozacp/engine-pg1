#include "window.h"

namespace GL
{
	Window::Window(float width, float height, std::string title)
	{
		this->glfWindow = NULL;
		this->height = height;
		this->width = width;
		this->title = title;
	}

	Window::~Window()
	{
	}

	GLFWwindow* Window::GetWindow()
	{
		return glfWindow;
	}

	bool Window::OpenWindow()
	{
		glfWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!glfWindow)
		{
			glfwTerminate();
			return false;
		}
		return true;
	}

	void Window::CloseWindow()
	{
		glfwTerminate();
	}

	void Window::DestroyWindow()
	{
		glfwDestroyWindow(glfWindow);
	}
}