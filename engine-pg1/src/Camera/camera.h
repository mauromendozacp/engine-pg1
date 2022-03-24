#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "Renderer/renderer.h"

namespace GL
{
	enum class CAMERA_TYPE
	{
		FPS,
		TPS,
		TOP_DOWN
	};

	class GRAPHICSENGINE_API Camera
	{
	public:
		Camera(Render* render);
		~Camera();

		void Init(float fov, float width, float height, float near, float far);

		void SetData(glm::vec3 pos, float sensitivity);
		void SetCameraType(CAMERA_TYPE cameraType);
		void SetFocus(glm::vec3 target, float distance);
		void SetPosition(glm::vec3 pos);
		void UseCamera();
		void Rotate();
		void Reset();

		glm::vec3 GetPosition();
		glm::vec3 GetFront();
		glm::vec3 GetUp();

		glm::mat4 GetView();
		glm::mat4 GetProjection();

		void SetFOV(float fov);
		float GetFOV();

		void SetSensitivity(float sensitivity);
		float GetSensitivity();

		void SetYaw(float yaw);
		float GetYaw();

		void SetPitch(float pitch);
		float GetPitch();

	private:
		Render* render;

		glm::mat4 view;
		glm::mat4 projection;

		uint uniformViewPosition;

		CAMERA_TYPE cameraType;
		glm::vec3 target;
		float distance;

		glm::vec3 pos;
		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;

		float fov;
		float aspect;
		float near;
		float far;

		float sensitivity;

		void UpdateDirection();
		void UpdateView();
		void UpdateProjection();
	};
}

#endif // !CAMERA_H