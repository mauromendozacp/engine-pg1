#ifndef MESH_H
#define MESH_H

#include "exports.h"
#include "vertexs.h"

#include "Renderer/renderer.h"
#include "Texture/texture.h"
#include "Material/material.h"
#include "Color/color.h"
#include "Material/SolidMaterial/solidMaterial.h"

#include <vector>

namespace GL
{
	class Mesh
	{
	public:
		Mesh();
		Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures);
		~Mesh();

		void Init();
		void Draw();
		void DeInit();

		std::vector<Vertex> GetVertexs();

		Material* material;
		Color color;

	private:		
		void SetUniforms();
		void UpdateShader();

		Render* render;
		std::vector<Vertex> vertexs;
		std::vector<uint> indexes;
		std::vector<Texture> textures;
		uint VAO, VBO, EBO;

		uint uniformColor;
		uint uniformAlpha;
		uint uniformBaseTexture;
		uint uniformUseTexture;

		uint locationPosition;
		uint locationNormal;
		uint locationTexCoord;
	};
}

#endif // !MESH_H