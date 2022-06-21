#include "thirdPersonCamera.h"

namespace GL
{
	ThirdPersonCamera::ThirdPersonCamera(Render* render) : Camera(render)
	{
		target = nullptr;
		offset = 0.f;
	}

	ThirdPersonCamera::~ThirdPersonCamera()
	{
	}

	void ThirdPersonCamera::Update()
	{
		UpdateDirection();
		UpdateProjection();
	}

	void ThirdPersonCamera::SetTarget(Entity* target)
	{
		this->target = target;
	}

	void ThirdPersonCamera::SetOffset(float offset)
	{
		this->offset = offset;
	}

	void ThirdPersonCamera::UpdateDirection()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		
		transform.forward = glm::normalize(direction);
		transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0.f, 1.f, 0.f)));
		transform.up = glm::normalize(glm::cross(transform.right, transform.forward));
		transform.position = target->GetPos() - transform.forward * offset;

		UpdateView();
	}

	void ThirdPersonCamera::UpdateView()
	{
		view = glm::lookAt(transform.position, target->GetPos(), transform.up);

		render->SetView(view);
	}
}