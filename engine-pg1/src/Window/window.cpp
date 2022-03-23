#include "window.h"

namespace GL
{
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

	Window::Window(float width, float height, std::string title)
	{
		this->glfWindow = nullptr;
		this->height = height;
		this->width = width;
		this->title = title;
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
		glfwMakeContextCurrent(glfWindow);
		glfwSetFramebufferSizeCallback(glfWindow, FramebufferSizeCallback);
		std::cout << glGetString(GL_VERSION) << std::endl;
	}

	GLFWwindow* Window::GetWindow()
	{
		return glfWindow;
	}

	bool Window::OpenWindow()
	{
		glfWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); 
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

	float Window::GetHeight()
	{
		return height;
	}

	float Window::GetWidth()
	{
		return width;
	}

	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}