#ifndef ENTITY_H
#define ENTITY_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include <../glm/gtc/type_ptr.hpp>

namespace GL
{
	class GRAPHICSENGINE_API Entity
	{

	public:
		Entity();
		Entity(Render* render);
		~Entity();

		void SetPos(float x, float y, float z);
		void SetPos(glm::vec3 pos);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);
		void SetScale(float size);
		void SetScale(float x, float y, float z);
		void SetColor(float r, float g, float b, float a);

		void SetCollider(bool col);
		void SetMoveable(bool mov);
		bool IsMoveable();
		bool HasCollider();

		float GetPosX();
		float GetPosY();
		float GetPosZ();

		float GetRotX();
		float GetRotY();
		float GetRotZ();

		float GetScaleX();
		float GetScaleY();
		float GetScaleZ();

		glm::vec3 GetPos();
		glm::mat4 GetRotation();
		glm::vec3 GetPivot();

		void Draw(unsigned int shaderId);
		void DeInit();

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
		glm::mat4 model;

		unsigned int VAO, VBO, EBO, tam, vertices;
		float *vertexs;
		bool hasCollider, moveable;

		void UpdateModel();
	};
}

#endif // !ENTITY_H