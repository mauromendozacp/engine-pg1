#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"
#include "vertexs.h"

#include "Material/material.h"
#include "Color/color.h"
#include "Importer/TextureImporter/textureImporter.h"

#include <vector>

namespace GL
{
	struct Mesh
	{
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;
	};

	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D();
		Entity3D(Render* render);
		~Entity3D();

		void Init();
		void Draw();
		void DeInit();

		void SetMesh(Mesh mesh);
		std::vector<Vertex> GetVertexs() override;

		Material* material;
		Color color;

	protected:
		Mesh mesh;

		uint VAO, VBO, EBO;

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