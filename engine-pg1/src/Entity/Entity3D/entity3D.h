#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"

#include "Material/material.h"
#include "Color/color.h"
#include "Importer/TextureImporter/textureImporter.h"

#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D();
		Entity3D(Render* render);
		Entity3D(std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures, Render* render);
		~Entity3D();

		void Init();
		void Draw();
		void DeInit();

		Material* material;
		Color color;

	protected:
		std::vector<Texture> textures;

		uint uniformColor;
		uint uniformAlpha;
		uint uniformAffectedLight;
		uint uniformUseTexture;
		uint uniformBaseTexture;

		bool affectedLight;

		virtual void SetUniforms() override;
		virtual void UpdateShader() override;
		void NodeDraw();
	};
}

#endif // !ENTITY3D_H