#ifndef VOLUME_AABB_H
#define	VOLUME_AABB_H

#include "Volume/volume.h"

namespace GL
{
	class GRAPHICSENGINE_API VolumeAABB : public Volume
	{
	public:
		VolumeAABB();
		~VolumeAABB();

		void Init(Render* render) override;
		void Update(glm::mat4 model) override;
		void Draw() override;

		bool IsOnFrustum() override;
		std::vector<Vertex> GetVertexs() override;
		void SetVolumeMinMax(glm::vec3 min, glm::vec3 max) override;
		void SetGlobalVolume(glm::vec3 center, float extX, float extY, float extZ);

		glm::vec3 center;
		glm::vec3 extents;

	private:
		bool IsOnPlane(Plane plane) override;		
	};
}

#endif // !VOLUME_H