#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"

#include <Material/material.h>
#include "Importer/ModelImporter/modelImporter.h"
#include "Mesh/mesh.h"

#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D(Render* render);
		~Entity3D();

		void Init(std::string path);
		void Draw();
		void DeInit();

		Material* material;

	private:
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;

		uint VAO, VBO, EBO;

		uint uniformAffectedLight;

		bool affectedLight;

		void SetUniforms(uint shaderId);

		void SetMeshData(Mesh* mesh, Entity3D* parent);
		void NodeDraw();
		void NodeDeInit();

		std::vector<Vertex> GetVertexs();
		std::vector<uint> GetIndexes();
		std::vector<Texture> GetTextures();

		uint GetVAO();
		uint GetVBO();
		uint GetEBO();
	};
}

#endif // !ENTITY3D_H