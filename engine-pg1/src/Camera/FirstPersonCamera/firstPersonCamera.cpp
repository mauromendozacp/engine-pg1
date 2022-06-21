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
			SetPos(GetPos() - glm::normalize(glm::cross(transform.forward, transform.up)) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_D) || GL::Input::IsKeyPressed(KEY_RIGHT))
		{
			SetPos(GetPos() + glm::normalize(glm::cross(transform.forward, transform.up)) * GetSpeedDelta());
		}
		else if (GL::Input::IsKeyPressed(KEY_W) || GL::Input::IsKeyPressed(KEY_UP))
		{
			SetPos(GetPos() + GetSpeedDelta() * transform.forward);
		}
		else if (GL::Input::IsKeyPressed(KEY_S) || GL::Input::IsKeyPressed(KEY_DOWN))
		{
			SetPos(GetPos() - GetSpeedDelta() * transform.forward);
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
		
		transform.forward = glm::normalize(direction);
		transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0.f, 1.f, 0.f)));
		transform.up = glm::normalize(glm::cross(transform.right, transform.forward));
		
		UpdateView();
	}

	void FirstPersonCamera::UpdateView()
	{
		view = glm::lookAt(transform.position, transform.position + transform.forward, transform.up);

		render->SetView(view);
	}
}