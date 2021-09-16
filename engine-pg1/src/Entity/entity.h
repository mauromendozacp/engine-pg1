#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "glm.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Entity
	{
	private:
		Render* render;
		glm::vec3 v3Pos;
		glm::vec3 v3Rot;
		glm::vec3 v3Scale;

		glm::mat4 translate;
		glm::mat4 rotationX;
		glm::mat4 rotationY;
		glm::mat4 rotationZ;
		glm::mat4 scale;

		glm::mat4 trs;

	public:
		Entity(Render* render);
		~Entity();
	};

	
}

#endif // !ENTITY_H