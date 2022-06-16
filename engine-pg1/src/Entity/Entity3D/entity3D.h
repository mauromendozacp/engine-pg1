#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"
#include "vertexs.h"

#include <Material/material.h>
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
		Entity3D(Render* render);
		~Entity3D();

		void Init();
		void Draw();
		void DeInit();

		void SetMesh(Mesh mesh);

		Material* material;

	private:
		Mesh mesh;

		uint VAO, VBO, EBO;

		uint uniformAffectedLight;
		uint uniformBaseTexture;
		std::vector<uint> uniformsTexture;

		bool affectedLight;

		void SetUniforms(uint shaderId);
		void NodeDraw();
	};
}

#endif // !ENTITY3D_H