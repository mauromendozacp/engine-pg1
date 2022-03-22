#include "camera.h"

namespace GL
{
	Camera::Camera(Render* render, Input* input)
	{
		this->render = render;
		this->input = input;

		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		cameraType = CAMERA_TYPE::FPS;
		target = glm::vec3(0.f);

		pos = glm::vec3(0.0f);
		front = glm::vec3(0.0f);
		up = glm::vec3(0.0f);

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
		front = glm::vec3(0.0f, 0.0f, -1.0f);
		up = glm::vec3(0.0f, 1.0f, 0.0f);
		aspect = width / height;
		this->fov = fov;
		this->near = near;
		this->far = far;

		UpdateView();
		UpdateProjection();
		input->SetFOV(fov);
	}

	void Camera::Update()
	{
		Rotate();
		Zoom();
	}

	void Camera::SetData(glm::vec3 pos, float sensitivity)
	{
		this->pos = pos;
		this->sensitivity = sensitivity;

		UpdateView();
	}

	void Camera::SetCameraType(CAMERA_TYPE cameraType)
	{
		this->cameraType = cameraType;
	}

	void Camera::SetFocus(glm::vec3 target, float distance)
	{
		this->target = target;
		this->distance = distance;
	}

	void Camera::SetPosition(glm::vec3 pos)
	{	
		switch (cameraType)
		{
		case GL::CAMERA_TYPE::FPS:
			this->pos = pos;
			break;
		case GL::CAMERA_TYPE::TPS:
			target = pos;
			break;
		case GL::CAMERA_TYPE::TOP_DOWN:
			break;
		default:
			break;
		}

		UpdateView();
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
		
		switch (cameraType)
		{
		case GL::CAMERA_TYPE::FPS:
			break;
		case GL::CAMERA_TYPE::TPS:
			pos = target - glm::normalize(direction) * distance;
			break;
		case GL::CAMERA_TYPE::TOP_DOWN:
			break;
		default:
			break;
		}

		UpdateView();
	}

	void Camera::Zoom()
	{
		if (fov != input->GetFOV())
		{
			fov = input->GetFOV();
			UpdateProjection();
		}
	}

	void Camera::Reset()
	{
		pos = glm::vec3(0.f);
		UpdateView();
	}

	void Camera::UpdateView()
	{
		switch (cameraType)
		{
		case GL::CAMERA_TYPE::FPS:
			view = glm::lookAt(pos, pos + front, up);
			break;
		case GL::CAMERA_TYPE::TPS:
			view = glm::lookAt(pos, target, up);
			break;
		case GL::CAMERA_TYPE::TOP_DOWN:
			break;
		default:
			break;
		}

		render->SetView(view);
	}

	void Camera::UpdateProjection()
	{
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
		render->SetProjection(projection);
	}
}