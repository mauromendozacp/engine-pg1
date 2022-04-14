#include "mesh.h"

namespace GL
{
	Mesh::Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<TextureData> textures)
	{
		this->render = render;
		this->vertexs = vertexs;
		this->indexes = indexes;
		this->textures = textures;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Init()
	{

	}

	void Mesh::Draw()
	{

	}
}