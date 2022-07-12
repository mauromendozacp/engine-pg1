#ifndef CAMERA_H
#define CAMERA_H

#include "Entity/entity.h"

#include "GLM/glm.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Camera : public Entity
	{
	public:
		Camera(Render* render);
		~Camera();

		void Init(float fov, float width, float height, float near, float far);
		void Update();
		void Rotate();
		void Reset();

		void SetFOV(float fov);
		void SetYaw(float yaw);
		void SetPitch(float pitch);
		void SetSensitivity(float sensitivity);
		void SetTarget(Entity* target);
		void SetOffset(float offset);
		void SetFollowStatus(bool status);

		float GetFOV();
		float GetYaw();
		float GetPitch();
		float GetSensitivity();

		float GetNear();
		float GetFar();
		float GetAspect();

	protected:
		void SetUniforms() override;
		void UpdateShader() override;

		void UpdateDirection();
		void UpdateView();
		void UpdateProjection();

		glm::mat4 view;
		glm::mat4 projection;

		uint uniformViewPosition;

		float yaw;
		float pitch;

		float fov;
		float aspect;
		float near;
		float far;

		float sensitivity;
	
		Entity* target;
		float offset;
		bool followTarget;
	};
}

#endif // !CAMERA_H