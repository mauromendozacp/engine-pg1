#ifndef OCCLUSION_CULLING_H
#define OCCLUSION_CULLING_H

#include "exports.h"
#include "Camera/camera.h"
#include "Plane/plane.h"

namespace GL
{
	class GRAPHICSENGINE_API OcclusionCulling
	{
	public:
		OcclusionCulling();
		~OcclusionCulling();

		static void Init(Camera* camera);
		static void Update();
		 
		static void SetCamera(Camera* camera);
		
		static Plane up;
		static Plane down;
		static Plane left;
		static Plane right;
		static Plane front;
		static Plane back;

	private:
		static Camera* camera;
		 
		static glm::vec3 pointBack;
		static glm::vec3 pointFront;
		static glm::vec3 pointTopLeft;
		static glm::vec3 pointTopRight;
		static glm::vec3 pointBottomLeft;
		static glm::vec3 pointBottomRight;
	};
}

#endif //!OCCLUSION_CULLING_H