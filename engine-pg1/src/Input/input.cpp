#include "input.h"

namespace GL
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	std::list<int> currentKeysDown;

	Input::Input(Window* window)
	{
		this->window = window;
	}

	Input::~Input()
	{
	}

	void Input::Init()
	{
		glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	}

	bool Input::IsKeyPressed(int keycode)
	{
		int aux = glfwGetKey(window->GetWindow(), keycode);
		return aux == GLFW_PRESS;
	}

	bool Input::IsKeyDown(int keycode)
	{
		std::list<int>::iterator it = find(currentKeysDown.begin(), currentKeysDown.end(), keycode);
		if (it != currentKeysDown.end())
		{
			currentKeysDown.remove(keycode);
			return true;
		}
		return false;
	}

	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			currentKeysDown.push_front(key);
		}
		else if (action == GLFW_RELEASE)
		{
			currentKeysDown.remove(key);
		}
	}
}