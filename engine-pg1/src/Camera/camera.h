#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/entity.h"

#include "GLM/glm.hpp"

namespace GL
{
	enum class CAMERA_TYPE
	{
		FPS,
		TPS,
		TOP_DOWN
	};

	class GRAPHICSENGINE_API Camera : public Entity
	{
	public:
		Camera(Render* render);
		~Camera();

		void Init(float fov, float width, float height, float near, float far);
		virtual void Update() = 0;

		void UseCamera();
		void Rotate();
		void Reset();

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

	protected:
		virtual void SetUniforms() override;
		virtual void UpdateDirection() = 0;
		virtual void UpdateView() = 0;
		void UpdateProjection();

		glm::mat4 view;
		glm::mat4 projection;

		uint uniformViewPosition;

		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;

		float fov;
		float aspect;
		float near;
		float far;

		float sensitivity;
	};
}

#endif // !CAMERA_H