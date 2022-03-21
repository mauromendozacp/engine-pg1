#include "camera.h"

namespace GL
{
	Camera::Camera(Render* render, Input* input)
	{
		this->render = render;
		this->input = input;

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

	void Camera::Init(float fov, float width, float height, float near, float far)
	{
		pos = glm::vec3(0.f);
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);

		UpdateView();
		projection = glm::perspective(glm::radians(fov), width / height, near, far);
		render->SetProjection(projection);
	}

	void Camera::Update(float deltaTime)
	{
		InputMove(deltaTime);
		Rotate();
	}

	void Camera::SetData(glm::vec3 pos, float speed, float sensitivity)
	{
		this->pos = pos;
		this->speed = speed;
		this->sensitivity = sensitivity;

		UpdateView();
	}

	void Camera::SetPosition(glm::vec3 pos)
	{
		this->pos = pos;
	}

	glm::vec3 Camera::GetPosition()
	{
		return pos;
	}

	glm::vec3 Camera::GetFront()
	{
		return front;
	}

	glm::vec3 Camera::GetUp()
	{
		return up;
	}

	glm::mat4 Camera::GetView()
	{
		return view;
	}

	glm::mat4 Camera::GetProjection()
	{
		return projection;
	}

	void Camera::InputMove(float deltaTime)
	{
		if (input->IsKeyPressed(KEY_W))
		{
			pos += speed * deltaTime * front;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_S))
		{
			pos -= speed * deltaTime * front;
			UpdateView();
		}

		if (input->IsKeyPressed(KEY_LEFT_SHIFT))
		{
			pos += speed * deltaTime * up;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_LEFT_CONTROL))
		{
			pos -= speed * deltaTime * up;
			UpdateView();
		}

		if (input->IsKeyPressed(KEY_A))
		{
			pos -= glm::normalize(glm::cross(front, up)) * speed * deltaTime;
			UpdateView();
		}
		else if (input->IsKeyPressed(KEY_D))
		{
			pos += glm::normalize(glm::cross(front, up)) * speed * deltaTime;
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
		render->SetView(view);
	}
}