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
	}

	void Camera::UseCamera()
	{
		render->UseShader();
		Entity::UpdateShader();
		render->UpdateVec3Value(uniformViewPosition, transform.position);
		render->CleanShader();
	}

	glm::mat4 Camera::GetView()
	{
		return view;
	}

	glm::mat4 Camera::GetProjection()
	{
		return projection;
	}

	void Camera::SetFOV(float fov)
	{
		this->fov = fov;
		UpdateProjection();
	}

	float Camera::GetFOV()
	{
		return fov;
	}

	void Camera::SetSensitivity(float sensitivity)
	{
		this->sensitivity = sensitivity;
	}

	float Camera::GetSensitivity()
	{
		return sensitivity;
	}

	void Camera::SetYaw(float yaw)
	{
		this->yaw = yaw;
	}

	float Camera::GetYaw()
	{
		return yaw;
	}

	void Camera::SetPitch(float pitch)
	{
		this->pitch = pitch;
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

	void Camera::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformViewPosition, "viewPosition");
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

	void Camera::UpdateProjection()
	{
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
		render->SetProjection(projection);
	}
}