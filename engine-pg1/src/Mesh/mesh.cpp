#include "mesh.h"

namespace GL
{
	Mesh::Mesh()
	{
        VAO = 0;
        VBO = 0;
        EBO = 0;

        vertexs = std::vector<Vertex>();
        indexes = std::vector<uint>();
        textures = std::vector<Texture>();

        meshSons = std::vector<Mesh*>();
        meshParent = nullptr;
        name = "";
        node = nullptr;
        isParent = false;
	}

	Mesh::~Mesh()
	{
	}

	void Mesh::Init(Render* render, std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures)
	{
        this->vertexs = vertexs;
        this->indexes = indexes;
        this->textures = textures;

        render->GenBuffers(VAO, VBO, EBO);
        
        if (vertexs.size() == 0)
        {
            render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), 0);
        }
        else
        {
            render->BindBuffer(VAO, VBO, vertexs.size() * sizeof(Vertex), &vertexs[0]);
        }

        if (indexes.size() == 0)
        {
            render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), 0);
        }
        else
        {
            render->BindIndexs(EBO, indexes.size() * sizeof(unsigned int), &indexes[0]);
        }

        render->SetBaseAttribs(0, 3, sizeof(Vertex), (void*)0);
        render->SetBaseAttribs(1, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        render->SetBaseAttribs(2, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        for (int i = 0; i < textures.size(); i++)
        {
            textures[i].type.erase(0, 7);
        }
	}

    void Mesh::DeInit()
    {
        vertexs.clear();
        indexes.clear();
        textures.clear();

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    std::vector<Vertex> Mesh::GetVertexs()
    {
        return vertexs;
    }

    std::vector<uint> Mesh::GetIndexes()
    {
        return indexes;
    }

    std::vector<Texture> Mesh::GetTextures()
    {
        return textures;
    }

    uint Mesh::GetVAO()
    {
        return VAO;
    }

    uint Mesh::GetVBO()
    {
        return VBO;
    }

    uint Mesh::GetEBO()
    {
        return EBO;
    }

    void Mesh::AddMeshSon(Mesh* meshSon)
    {
        meshSons.push_back(meshSon);
    }

    void Mesh::SetMeshParent(Mesh* meshParent)
    {
        this->meshParent = meshParent;
    }

    void Mesh::SetName(std::string name)
    {
        this->name = name;
    }

    void Mesh::SetNode(aiNode* node)
    {
        this->node = node;
    }

    void Mesh::SetIsParent(bool isParent)
    {
        this->isParent = isParent;
    }

    std::vector<Mesh*> Mesh::GetMeshSons()
    {
        return meshSons;
    }

    Mesh* Mesh::GetMeshParent()
    {
        return meshParent;
    }

    std::string Mesh::GetName()
    {
        return name;
    }

    aiNode* Mesh::GetNode()
    {
        return node;
    }

    bool Mesh::IsParent()
    {
        return isParent;
    }
}