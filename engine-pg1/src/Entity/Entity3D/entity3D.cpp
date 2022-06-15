#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		material = nullptr;

		vertexs = std::vector<Vertex>();
		indexes = std::vector<uint>();
		textures = std::vector<Texture>();		

		VAO = 0;
		VBO = 0;
		EBO = 0;

		uniformAffectedLight = 0;
		uniformsTexture = std::vector<uint>();

		affectedLight = true;
	}

	Entity3D::~Entity3D()
	{
	}

	void Entity3D::Init(std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures)
	{
		this->vertexs = vertexs;
		this->indexes = indexes;
		this->textures = textures;

		SetUniforms(render->GetTextureShaderId());

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

		render->SetBaseAttribs(locationPosition, 3, sizeof(Vertex), (void*)0);
		render->SetBaseAttribs(locationNormal, 3, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		render->SetBaseAttribs(locationTexCoord, 2, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		for (int i = 0; i < this->textures.size(); i++)
		{
			this->textures[i].type.erase(0, 7);
		}
	}

	void Entity3D::Draw()
	{
		render->UseShader(render->GetTextureShaderId());
		render->BlendEnable();
		render->TextureEnable();
		
		NodeDraw();

		render->TextureDisable();
		render->BlendDisable();
		render->CleanShader();
	}

	void Entity3D::DeInit()
	{
		render->UnBind(VAO, VBO, EBO);

		vertexs.clear();
		indexes.clear();
		textures.clear();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->DeInit();
		}
	}
	
	void Entity3D::SetUniforms(uint shaderId)
	{
		Entity::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformAffectedLight, "affectedLight");
	}

	void Entity3D::NodeDraw()
	{
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		render->UpdateStatus(uniformAffectedLight, affectedLight);

		if (material != nullptr)
		{
			material->UpdateShader();
		}

		for (int i = 0; i < textures.size(); i++)
		{
			render->UseTexture(i, textures[i].id);
		}

		render->DrawMesh(VAO, indexes.size());
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->NodeDraw();
		}
	}
}