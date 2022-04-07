#include "firstPersonCamera.h"

namespace GL
{
	FirstPersonCamera::FirstPersonCamera(Render* render) : Camera(render)
	{
	}

	FirstPersonCamera::~FirstPersonCamera()
	{
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