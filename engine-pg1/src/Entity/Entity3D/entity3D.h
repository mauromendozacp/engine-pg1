#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Entity/entity.h"

#include <Material/material.h>
#include "Importer/TextureImporter/textureImporter.h"

#include <vector>

namespace GL
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class GRAPHICSENGINE_API Entity3D : public Entity
	{
	public:
		Entity3D(Render* render);
		~Entity3D();

		void Init(std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures);
		void Draw();
		void DeInit();

		Material* material;

	private:
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;

		uint VAO, VBO, EBO;

		uint uniformAffectedLight;
		std::vector<uint> uniformsTexture;

		bool affectedLight;

		void SetUniforms(uint shaderId);
		void NodeDraw();
	};
}

#endif // !ENTITY3D_H