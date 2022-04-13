#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "exports.h"
#include "Input/input.h"
#include "Timer/timer.h"
#include "Camera/camera.h"

namespace GL
{
	class GRAPHICSENGINE_API FirstPersonCamera : public Camera
	{
	public:
		FirstPersonCamera(Render* render);
		~FirstPersonCamera();

		void Update() override;

		void SetSpeed(float speed);

	private:
		float speed;

		float GetSpeedDelta();

		void UpdateDirection() override;
		void UpdateView() override;
	};
}

#endif // !FIRST_PERSON_CAMERA_H