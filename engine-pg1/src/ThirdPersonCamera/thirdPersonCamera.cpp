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
		front = glm::normalize(direction);

		transform.position = target->GetPos() - front * offset;

		UpdateView();
	}

	void ThirdPersonCamera::UpdateView()
	{
		view = glm::lookAt(transform.position, target->GetPos(), up);

		render->SetView(view);
	}
}