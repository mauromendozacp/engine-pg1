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

		void UpdateShader();
		void Draw();
		void DeInit();

		void SetColor(glm::vec4 color);
		void SetColor(float r, float g, float b, float a);
		glm::vec4 GetColor();

		void SetCollider(bool hasCollider);
		void SetMoveable(bool moveable);
		void SetAffectedLight(bool affectedLight);

		bool IsMoveable();
		bool HasCollider();
		bool IsAffectedLight();

	protected:
		glm::vec4 color;

		uint uniformBaseColor;
		uint uniformLightColor;
		uint uniformAlpha;
		uint uniformUseTexture;
		uint uniformAffectedLight;

		uint VAO, VBO, EBO, tam, vertices;
		float* vertexs;
		bool hasCollider;
		bool moveable;

		bool useTexture;
		bool affectedLight;

		void SetUniforms();
	};
}

#endif // !ENTITY2D_H
