#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity/entity.h"

namespace GL
{
	class GRAPHICSENGINE_API Entity2D : public Entity
	{
	public:
		Entity2D();
		Entity2D(Render* render);
		~Entity2D();

		void SetColor(glm::vec4 color);
		void SetColor(float r, float g, float b, float a);
		glm::vec4 GetColor();

		void SetCollider(bool col);
		void SetMoveable(bool mov);
		bool IsMoveable();
		bool HasCollider();

		void Draw(unsigned int shaderId);
		void DeInit();

	protected:
		glm::vec4 color;

		uint uniformColor;
		uint uniformAlpha;

		uint VAO, VBO, EBO, tam, vertices;
		float* vertexs;
		bool hasCollider, moveable;

		void SetUniforms(uint shaderId);
	};
}

#endif // !ENTITY2D_H
