#ifndef OCCLUSION_CULLING_H
#define OCCLUSION_CULLING_H

#include "exports.h"
#include "Entity/entity.h"
#include "Camera/camera.h"
#include "Plane/plane.h"

#include <list>
#include <math.h>

namespace GL
{
	class GRAPHICSENGINE_API OcclusionCulling
	{
	public:
		OcclusionCulling();
		~OcclusionCulling();

		void Init(Camera* camera);
		void Update();

		void SetCamera(Camera* camera);
		void AddEntity(Entity* entity);

		Plane up;
		Plane down;
		Plane left;
		Plane right;
		Plane front;
		Plane back;

	private:
		void UpdatePlanes();
		void UpdateEntitiesDraw(Entity* entity);

		std::list<Entity*> entities;
		Camera* camera;

		glm::vec3 pointBack;
		glm::vec3 pointFront;
		glm::vec3 pointTopLeft;
		glm::vec3 pointTopRight;
		glm::vec3 pointBottomLeft;
		glm::vec3 pointBottomRight;
	};
}

#endif //!OCCLUSION_CULLING_H