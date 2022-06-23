#ifndef VOLUME_H
#define	VOLUME_H

#include "exports.h"
#include "vertexs.h"

#include "Plane/plane.h"
#include "OcclusionCulling/occlusionCulling.h"

#include "GLM/glm.hpp"
#include <vector>
#include <list>

class Entity {};

namespace GL
{
	class GRAPHICSENGINE_API Volume
	{
	public:
		Volume() { };
		~Volume() { };

		virtual bool IsOnFrustum(std::list<Entity*> nodes, ) = 0;

	protected:
		virtual bool IsOnPlane(Plane plane) = 0;
	};
}

#endif // !VOLUME_H