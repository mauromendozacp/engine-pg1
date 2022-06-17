#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity/entity.h"
#include "vertexs.h"

#include "Color/color.h"
#include "Material/material.h"

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
		Material* material;

	protected:
		uint uniformColor;
		uint uniformAlpha;
		uint uniformAffectedLight;
		uint uniformUseTexture;

		uint VAO, VBO, EBO, tam, vertices;
		float* vertexs;
		bool hasCollider;
		bool moveable;

		bool affectedLight;
		bool useTexture;

		virtual void SetUniforms() override;
	};
}

#endif // !ENTITY2D_H
