#include "mesh.h"

namespace GL
{
	Mesh::Mesh(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures)
	{
		this->render = render;
		this->vertexs = vertexs;
		this->indexes = indexes;
		this->textures = textures;

        Init();
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Init()
	{
        render->GenBuffers(VAO, VBO, EBO);
        render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
        render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);

        render->SetBaseAttribs(0, 3, sizeof(Vertex), (void*)0);
        render->SetBaseAttribs(1, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        render->SetBaseAttribs(2, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        for (int i = 0; i < textures.size(); i++)
        {
            textures[i].type.erase(0, 7);
        }
	}

	void Mesh::Draw()
	{
        for (uint i = 0; i < textures.size(); i++)
        {
            render->ActiveTexture(i);

            std::string loc = "material." + textures[i].type;
            render->UpdateMaterialValue(render->GetTextureShaderId(), i, loc.c_str());
            render->BindTexture(textures[i].id);
        }

        render->DrawMesh(VAO, indexes.size());
        render->ActiveTexture(0);
	}
}