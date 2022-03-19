#include "input.h"

namespace GL
{
	void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallback(GLFWwindow* window, double posX, double posY);

	std::list<int> currentKeysDown;
	glm::vec2 lastPos;
	glm::vec2 offsetPos;
	bool firstMouse;

	Input::Input(Window* window)
	{
		this->window = window;
	}

	Input::~Input()
	{
	}

	void Input::Init()
	{
		firstMouse = true;
		glfwSetKeyCallback(window->GetWindow(), KeyCallback);
		glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

	glm::vec2 Input::GetLastPosition()
	{
		return lastPos;
	}

	glm::vec2 Input::GetOffsetPosition()
	{
		return offsetPos;
	}

	void Input::SetOffsetPosition(glm::vec2 offset)
	{
		offsetPos = offset;
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

	void MouseCallback(GLFWwindow* window, double posX, double posY)
	{
		if (firstMouse)
		{
			lastPos.x = posX;
			lastPos.y = posY;
			firstMouse = false;
		}

		offsetPos.x = posX - lastPos.x;
		offsetPos.y = lastPos.y - posY;

		lastPos.x = posX;
		lastPos.y = posY;

		std::cout << "pos x: " << lastPos.x << " - pos y: " << lastPos.y;
	}
}