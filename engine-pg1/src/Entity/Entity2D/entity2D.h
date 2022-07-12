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

		glm::vec3 minAABB;
		glm::vec3 maxAABB;

	protected:
		uint uniformColor;
		uint uniformAlpha;
		uint uniformAffectedLight;
		uint uniformUseTexture;

		uint VAO, VBO, EBO;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;

		bool hasCollider;
		bool moveable;

		bool affectedLight;
		bool useTexture;

		virtual void SetUniforms() override;
		virtual void UpdateShader() override;
		void GenerateVolumeAABB();
	};
}

#endif // !ENTITY2D_H
