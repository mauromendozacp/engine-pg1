#include "camera.h"

namespace GL
{
	Camera::Camera()
	{
		input = nullptr;
		timer = nullptr;

		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		pos = glm::vec3(0.0f);
		front = glm::vec3(0.0f);
		up = glm::vec3(0.0f);

		yaw = -90.f;
		pitch = 0.f;

		speed = 0.f;
		sensitivity = 0.f;
	}

	Camera::~Camera()
	{
	}

	void Camera::Init(Input* input, Timer* timer, float fov, float width, float height, float near, float far)
	{
		this->input = input;
		this->timer = timer;

		pos = glm::vec3(0.f);
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		UpdateView();
		projection = glm::perspective(glm::radians(fov), width / height, near, far);
	}

	void Camera::Update()
	{
		InputMove();
		Rotate();
	}

	void Camera::SetData(glm::vec3 pos, float speed, float sensitivity)
	{
		this->pos = pos;
		this->speed = speed;
		this->sensitivity = sensitivity;

		UpdateView();
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
		float deltaSpeed = speed * timer->GetDeltaTime();

		if (input->IsKeyPressed(KEY_W))
		{
			pos += deltaSpeed * front;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			pos -= deltaSpeed * front;
			UpdateView();
		}

		if (input->IsKeyPressed(KEY_LEFT_SHIFT))
		{
			pos += deltaSpeed * up;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_LEFT_CONTROL))
		{
			pos -= deltaSpeed * up;
			UpdateView();
		}

		if (input->IsKeyPressed(KEY_A))
		{
			pos -= glm::normalize(glm::cross(front, up)) * deltaSpeed;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			pos += glm::normalize(glm::cross(front, up)) * deltaSpeed;
			UpdateView();
		}

		if (input->IsKeyPressed(KEY_R))
		{
			pos = glm::vec3(0.f);
			UpdateView();
		}
	}

	void Camera::Rotate()
	{
		glm::vec2 offsetPos = input->GetOffsetPosition();
		offsetPos.x *= sensitivity;
		offsetPos.y *= sensitivity;
		input->SetOffsetPosition(offsetPos);

		yaw += offsetPos.x;
		pitch += offsetPos.y;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);

		UpdateView();
	}

	void Camera::UpdateView()
	{
		view = glm::lookAt(pos, pos + front, up);
	}
}