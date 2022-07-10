#ifndef VOLUME_H
#define	VOLUME_H

#include "exports.h"

#include "Plane/plane.h"
#include "Line/line.h"

#include "GLM/glm.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Volume
	{
	public:
		Volume();
		~Volume();
		
		virtual void Init(Render* render) = 0;
		virtual void Update(glm::mat4 model) = 0;
		virtual void Draw() = 0;
		void DeInit();

		virtual void SetVolumeMinMax(glm::vec3 min, glm::vec3 max) = 0;
		virtual bool IsOnFrustum() = 0;
		virtual std::vector<Vertex> GetVertexs() = 0;

		Line* lines;

	protected:
		virtual bool IsOnPlane(Plane plane) = 0;
	};
}

#endif // !VOLUME_H