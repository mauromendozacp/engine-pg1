#include "firstPersonCamera.h"

namespace GL
{
	FirstPersonCamera::FirstPersonCamera(Render* render) : Camera(render)
	{
		speed = 0.f;
	}

	FirstPersonCamera::~FirstPersonCamera()
	{
	}

	void FirstPersonCamera::SetSpeed(float speed)
	{
		this->speed = speed;
	}

	void FirstPersonCamera::Update()
	{
		if (Input::IsKeyPressed(KEY_A) || Input::IsKeyPressed(KEY_LEFT))
		{
			SetPos(GetPos() - glm::normalize(glm::cross(front, up)) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_D) || GL::Input::IsKeyPressed(KEY_RIGHT))
		{
			SetPos(GetPos() + glm::normalize(glm::cross(front, up)) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_W) || GL::Input::IsKeyPressed(KEY_UP))
		{
			SetPos(GetPos() + GetSpeedDelta() * front);
		}
		else if (GL::Input::IsKeyPressed(KEY_S) || GL::Input::IsKeyPressed(KEY_DOWN))
		{
			SetPos(GetPos() - GetSpeedDelta() * front);
		}

		UpdateDirection();
		UpdateProjection();
	}

	float FirstPersonCamera::GetSpeedDelta()
	{
		return speed * Timer::GetDeltaTime();
	}

	void FirstPersonCamera::UpdateDirection()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);

		UpdateView();
	}

	void FirstPersonCamera::UpdateView()
	{
		view = glm::lookAt(transform.position, transform.position + front, up);

		render->SetView(view);
	}
}