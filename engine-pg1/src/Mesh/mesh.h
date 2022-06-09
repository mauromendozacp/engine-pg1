#ifndef MESH_H
#define MESH_H

#include "exports.h"

#include "Renderer/renderer.h"
#include "Importer/TextureImporter/textureImporter.h"

#include "GLM/ext/matrix_transform.hpp"

#include <vector>
#include <string>

#define MAX_BONE_INFLUENCE 4

namespace GL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		glm::vec3 Tangent;
		glm::vec3 Bitangent;
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	class GRAPHICSENGINE_API Mesh
	{
	public:
		Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures);
		~Mesh();

		void Init();
		void Draw();
		void DeInit();

	private:
		Render* render;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;

		uint VAO, VBO, EBO;
	};
}

#endif // !MESH_H
