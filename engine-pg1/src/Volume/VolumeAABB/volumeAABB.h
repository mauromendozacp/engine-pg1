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

		void Init(Render* render) override;
		void Draw(glm::mat4 model) override;

		bool IsOnFrustum() override;
		std::vector<Vertex> GetVertexs() override;

		void SetGlobalVolume(Volume* volume, glm::mat4 model) override;
		void SetVolume(glm::vec3 center, float extX, float extY, float extZ);

		glm::vec3 center;
		glm::vec3 extents;

	private:
		bool IsOnPlane(Plane plane) override;		
	};
}

#endif // !VOLUME_H