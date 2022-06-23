#ifndef VOLUME_H
#define	VOLUME_H

#include "exports.h"

#include "transform.h"
#include "matrix.h"
#include "vertexs.h"

#include "Plane/plane.h"

#include "GLM/glm.hpp"

#include <vector>
#include <list>

namespace GL
{
	class GRAPHICSENGINE_API Volume
	{
	public:
		Volume() { };
		~Volume() { };

		virtual bool IsOnFrustum(Transform transform, Matrix matrix) = 0;

	protected:
		virtual bool IsOnPlane(Plane plane) = 0;
	};
}

#endif // !VOLUME_H