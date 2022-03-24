#include "input.h"

namespace GL
{
	Window* Input::window = nullptr;
	Camera* Input::camera = nullptr;

	std::list<int> Input::currentKeysDown = std::list<int>();
	glm::vec2 Input::lastPos = glm::vec2(0.f);
	bool Input::firstMouse = true;

	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	void Input::Init(Window* wind, Camera* cam)
	{
		window = wind;
		SetCamera(cam);

		glfwSetKeyCallback(window->GetWindow(), KeyCallback);
		glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetScrollCallback(window->GetWindow(), ScrollCallback);
	}

	void Input::SetCamera(Camera* cam)
	{
		camera = cam;
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

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
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

	void Input::MouseCallback(GLFWwindow* window, double posX, double posY)
	{
		if (firstMouse)
		{
			lastPos.x = posX;
			lastPos.y = posY;
			firstMouse = false;
		}

		glm::vec2 offsetPos;
		offsetPos.x = posX - lastPos.x;
		offsetPos.y = lastPos.y - posY;

		lastPos.x = posX;
		lastPos.y = posY;

		offsetPos.x *= camera->GetSensitivity();
		offsetPos.y *= camera->GetSensitivity();

		camera->SetYaw(camera->GetYaw() + offsetPos.x);
		camera->SetPitch(camera->GetPitch() + offsetPos.y);

		camera->Rotate();
	}

	void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera->SetFOV(camera->GetFOV() - (float)yoffset);
		if (camera->GetFOV() < 1.0f)
			camera->SetFOV(1.0f);
		if (camera->GetFOV() > 45.0f)
			camera->SetFOV(45.0f);
	}
}