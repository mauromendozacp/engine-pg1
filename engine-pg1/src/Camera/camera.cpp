#include "camera.h"

namespace GL
{
	Camera::Camera(Render* render) : Entity(render)
	{
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		uniformViewPosition = 0;

		yaw = -90.f;
		pitch = 0.f;

		fov = 0.f;
		aspect = 0.f;
		near = 0.f;
		far = 0.f;

		sensitivity = 0.f;

		target = nullptr;
		offset = 0.f;
		followTarget = false;
	}

	Camera::~Camera()
	{
	}

	void Camera::Init(float fov, float width, float height, float near, float far)
	{
		aspect = width / height;
		this->fov = fov;
		this->near = near;
		this->far = far;

		SetUniforms();
		UpdateProjection();
	}

	void Camera::Update()
	{
		UpdateDirection();
		UpdateProjection();
		UpdateShader();
	}

	void Camera::Rotate()
	{
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		UpdateDirection();
	}

	void Camera::Reset()
	{
		transform.position = glm::vec3(0.f);
		UpdateView();
	}

	void Camera::SetFOV(float fov)
	{
		this->fov = fov;
		UpdateProjection();
	}

	void Camera::SetYaw(float yaw)
	{
		this->yaw = yaw;
	}

	void Camera::SetPitch(float pitch)
	{
		this->pitch = pitch;
	}

	void Camera::SetTarget(Entity* target)
	{
		this->target = target;
	}

	void Camera::SetSensitivity(float sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	void Camera::SetOffset(float offset)
	{
		this->offset = offset;
	}

	void Camera::SetFollowStatus(bool status)
	{
		followTarget = status;
	}

	float Camera::GetFOV()
	{
		return fov;
	}

	float Camera::GetSensitivity()
	{
		return sensitivity;
	}

	float Camera::GetYaw()
	{
		return yaw;
	}

	float Camera::GetPitch()
	{
		return pitch;
	}

	float Camera::GetNear()
	{
		return near;
	}

	float Camera::GetFar()
	{
		return far;
	}

	float Camera::GetAspect()
	{
		return aspect;
	}

	void Camera::UpdateDirection()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		transform.forward = glm::normalize(direction);
		transform.right = glm::normalize(glm::cross(transform.forward, glm::vec3(0.f, 1.f, 0.f)));
		transform.up = glm::normalize(glm::cross(transform.right, transform.forward));

		if (target != nullptr)
		{
			if (followTarget)
			{
				transform.position = target->GetPos() - transform.forward * offset;
			}
			else
			{
				transform.position = target->GetPos() - transform.forward;
			}
		}

		UpdateView();
	}

	void Camera::UpdateView()
	{
		glm::vec3 position = transform.position;
		if (target != nullptr)
		{
			position = target->GetPos();
		}

		if (followTarget)
		{
			view = glm::lookAt(transform.position, position, transform.up);
		}
		else
		{
			view = glm::lookAt(transform.position, position + transform.forward, transform.up);
		}

		render->SetView(view);
	}

	void Camera::UpdateProjection()
	{
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
		render->SetProjection(projection);
	}

	void Camera::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformViewPosition, "viewPosition");
	}

	void Camera::UpdateShader()
	{
		render->UseShader();
		Entity::UpdateShader();
		render->UpdateVec3Value(uniformViewPosition, transform.position);
		render->CleanShader();
	}

	void Camera::GenerateVolumeAABB()
	{
	}
}