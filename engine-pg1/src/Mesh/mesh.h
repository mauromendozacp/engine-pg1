#ifndef MESH_H
#define MESH_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "TextureImporter/textureImporter.h"
#include "../glm/ext/matrix_transform.hpp"
#include <vector>

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
		Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<TextureData> textures);
		~Mesh();

		void Init();
		void Draw();

	private:
		Render* render;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<TextureData> textures;
	};

	
}

#endif // !MESH_H
