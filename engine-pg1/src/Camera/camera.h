#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "Entity/entity.h"

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
		void Update();

		void SetData(Entity* target, float sensitivity, float offset);
		void SetCameraType(CAMERA_TYPE cameraType);
		void SetTarget(Entity* target);
		void UseCamera();
		void Rotate();
		void Reset();
		void UpdateDirection();

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
		Entity* target;
		float offset;

		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;

		float fov;
		float aspect;
		float near;
		float far;

		float sensitivity;

		void UpdateView();
		void UpdateProjection();
	};
}

#endif // !CAMERA_H