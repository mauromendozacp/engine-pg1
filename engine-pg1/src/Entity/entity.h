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
		Entity();
		Entity(Render* render);
		~Entity();

		void SetPos(float x, float y, float z);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		void SetScale(float x, float y, float z);
		void SetColor(glm::vec4 color);

		glm::mat4 GetRotation();
		void UpdateTRS();

		float GetPosX();
		float GetPosY();
		float GetPosZ();

		float GetRotX();
		float GetRotY();
		float GetRotZ();

		float GetScaleX();
		float GetScaleY();
		float GetScaleZ();

		virtual void Draw() = 0;

	protected:
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

		unsigned int VAO, VBO, EBO, vertices;
	};

	
}

#endif // !ENTITY_H