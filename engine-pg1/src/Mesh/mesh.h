#ifndef MESH_H
#define MESH_H

#include "exports.h"

#include "Renderer/renderer.h"
#include "Importer/TextureImporter/textureImporter.h"

#include "GLM/ext/matrix_transform.hpp"

#include <vector>
#include <string>

#define MAX_BONE_INFLUENCE 4

struct aiNode;

namespace GL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class GRAPHICSENGINE_API Mesh
	{
	public:
		Mesh();
		~Mesh();

		void Init(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures);
		void DeInit();

		std::vector<Vertex> GetVertexs();
		std::vector<uint> GetIndexes();
		std::vector<Texture> GetTextures();

		uint GetVAO();
		uint GetVBO();
		uint GetEBO();

		void AddMeshSon(Mesh* meshSon);
		void SetMeshParent(Mesh* meshParent);
		void SetName(std::string name);
		void SetNode(aiNode* node);
		void SetIsParent(bool isParent);

		std::vector<Mesh*> GetMeshSons();
		Mesh* GetMeshParent();
		std::string GetName();
		aiNode* GetNode();
		bool IsParent();

	private:
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;

		std::vector<Mesh*> meshSons;
		Mesh* meshParent;
		std::string name;
		aiNode* node;
		bool isParent;

		uint VAO, VBO, EBO;
	};
}

#endif // !MESH_H
