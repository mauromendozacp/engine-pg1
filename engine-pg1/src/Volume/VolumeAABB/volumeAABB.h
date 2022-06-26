#ifndef VOLUME_AABB_H
#define	VOLUME_AABB_H

#include "Volume/volume.h"

namespace GL
{
	#define MAX_BOUNDS 8

	class GRAPHICSENGINE_API VolumeAABB : public Volume
	{
	public:
		VolumeAABB();
		VolumeAABB(glm::vec3 min, glm::vec3 max);
		VolumeAABB(glm::vec3 center, float extX, float extY, float extZ);
		~VolumeAABB();

		bool IsOnFrustum(Transform transform, glm::mat4 worldModel) override;

		glm::vec3 center;
		glm::vec3 extents;

	private:
		bool IsOnPlane(Plane plane) override;
	};
}

#endif // !VOLUME_H