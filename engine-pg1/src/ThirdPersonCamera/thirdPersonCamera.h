#ifndef THIRD_PERSON_CAMERA_H
#define THIRD_PERSON_CAMERA_H

#include "exports.h"
#include "Camera/camera.h"

namespace GL
{
	class GRAPHICSENGINE_API ThirdPersonCamera : public Camera
	{
	public:
		ThirdPersonCamera(Render* render);
		~ThirdPersonCamera();

		void SetTarget(Entity* target);
		void SetOffset(float offset);

	private:
		Entity* target;
		float offset;

		void UpdateDirection() override;
		void UpdateView() override;
	};
}

#endif // !THIRD_PERSON_CAMERA_H