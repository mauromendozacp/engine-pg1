#ifndef VOLUME_H
#define	VOLUME_H

#include "exports.h"
#include "OcclusionCulling/occlusionCulling.h"

#include "GLM/glm.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Volume
	{
	public:
		Volume() { };
		~Volume() { };

		virtual bool IsOnFrustum(OcclusionCulling* frustum, Entity* entity) = 0;

	protected:
		virtual bool IsOnPlane(Plane plane) = 0;
	};
}

#endif // !VOLUME_H