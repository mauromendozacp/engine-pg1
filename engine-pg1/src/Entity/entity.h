#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Entity
	{

	public:
		Entity(Render* render);
		~Entity();

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

		glm::vec4 color;
		glm::mat4 trs;

		void SetTranslate(float x, float y, float z);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		glm::mat4 Rotation();
		void SetScale(float x, float y, float z);
		void UpdateTRS();
		void SetColor(glm::vec4 color);
	};

	
}

#endif // !ENTITY_H