#ifndef VOLUME_AABB_H
#define	VOLUME_AABB_H

#include "Volume/volume.h"

namespace GL
{
	class GRAPHICSENGINE_API VolumeAABB : public Volume
	{
	public:
		VolumeAABB();
		VolumeAABB(glm::vec3 min, glm::vec3 max);
		VolumeAABB(glm::vec3 center, float extX, float extY, float extZ);
		~VolumeAABB();

		bool IsOnFrustum(OcclusionCulling* frustum, Entity* entity) override;

		static VolumeAABB GenerateVolumeAABB(Entity* entity);

	private:
		bool IsOnPlane(Plane plane) override;

		glm::vec3 center;
		glm::vec3 extents;
	};
}

#endif // !VOLUME_H