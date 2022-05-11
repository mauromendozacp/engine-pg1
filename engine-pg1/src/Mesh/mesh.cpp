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
        render->SetBaseAttribs(3, 3, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        render->SetBaseAttribs(4, 3, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        render->SetBaseAttribs(5, 4, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));
        render->SetBaseAttribs(6, 4, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));

        render->ClearVertexArray();
	}

	void Mesh::Draw()
	{
        uint diffuseNr = 1;
        uint specularNr = 1;
        uint normalNr = 1;
        uint heightNr = 1;

        for (uint i = 0; i < textures.size(); i++)
        {
            render->ActiveTexture(i);

            std::string number;
            std::string name = textures[i].type;
            if (name == "diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "specular")
                number = std::to_string(specularNr++);
            else if (name == "normal")
                number = std::to_string(normalNr++);
            else if (name == "height")
                number = std::to_string(heightNr++);

            std::string loc = "material." + name + number;
            render->UpdateMaterialValue(render->GetTextureShaderId(), i, loc.c_str());
            render->BindTexture(textures[i].id);
        }

        render->DrawMesh(VAO, indexes.size());
        render->ActiveTexture(0);
	}
}