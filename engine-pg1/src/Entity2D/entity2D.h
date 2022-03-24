#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity/entity.h"
#include "Color/color.h"

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

		void SetCollider(bool hasCollider);
		void SetMoveable(bool moveable);
		void SetAffectedLight(bool affectedLight);

		bool IsMoveable();
		bool HasCollider();
		bool IsAffectedLight();

		Color color;

	protected:
		uint uniformColor;
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
