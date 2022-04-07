#ifndef FIRST_PERSON_CAMERA_H
#define FIRST_PERSON_CAMERA_H

#include "exports.h"
#include "Camera/camera.h"

namespace GL
{
	class GRAPHICSENGINE_API FirstPersonCamera : public Camera
	{
	public:
		FirstPersonCamera(Render* render);
		~FirstPersonCamera();

	private:
		void UpdateDirection() override;
		void UpdateView() override;
	};
}

#endif // !FIRST_PERSON_CAMERA_H