#ifndef ENTITY2D_H
#define ENTITY2D_H

#include "Entity/entity.h"

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
		
		void Draw() override;
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

		uint tam, indices;
		float* vertices;
		bool hasCollider;
		bool moveable;

		bool affectedLight;
		bool useTexture;

		virtual void SetUniforms() override;
		virtual void UpdateShader() override;
	};
}

#endif // !ENTITY2D_H
