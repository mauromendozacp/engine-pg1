#include "camera.h"

namespace GL
{
	Camera::Camera()
	{
		input = nullptr;

		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		pos = glm::vec3(1.0f);
		front = glm::vec3(1.0f);
		up = glm::vec3(1.0f);

		speed = 0.f;
		sensitivity = 0.f;
	}

	Camera::~Camera()
	{
	}

	void Camera::Init(glm::vec3 position, float fov, float width, float height, float near, float far)
	{
		pos = position;
		view = glm::lookAt(position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}

	void Camera::Update()
	{
		InputMove();
		InputAxis();
	}

	glm::mat4 Camera::GetView()
	{
		return view;
	}

	glm::mat4 Camera::GetProjection()
	{
		return projection;
	}

	void Camera::InputMove()
	{
		if (input->IsKeyDown(KEY_W))
		{
			pos += speed * front;
		}
		else if (input->IsKeyDown(KEY_S))
		{
			pos -= speed * front;
		}

		if (input->IsKeyDown(KEY_A))
		{
			pos -= glm::normalize(glm::cross(front, up)) * speed;
		}
		else if (input->IsKeyDown(KEY_D))
		{
			pos += glm::normalize(glm::cross(front, up)) * speed;
		}
	}

	void Camera::InputAxis()
	{

	}
}