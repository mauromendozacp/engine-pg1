#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D() : Entity()
	{
		textures = std::vector<Texture>();

		material = nullptr;
		color = Color();

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;
		uniformBaseTexture = 0;

		affectedLight = true;
	}

	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		textures = std::vector<Texture>();

		material = nullptr;
		color = Color();

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;
		uniformBaseTexture = 0;

		affectedLight = true;
	}

	Entity3D::Entity3D(std::vector<Vertex> vertexs, std::vector<uint> indexes, std::vector<Texture> textures, Render* render) : Entity(vertexs, indexes, render)
	{
		this->textures = textures;

		material = nullptr;
		color = Color();

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;
		uniformBaseTexture = 0;

		affectedLight = true;
	}

	Entity3D::~Entity3D()
	{
	}

	void Entity3D::Init()
	{
		SetUniforms();

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
	}

	void Entity3D::Draw()
	{
		render->UseShader();
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

		if (textures.size() > 0)
		{
			//render->TextureDelete(uniformBaseTexture, mesh.textures[0].id);
		}

		vertexs.clear();
		indexes.clear();
		textures.clear();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->DeInit();
		}
	}
	
	void Entity3D::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformColor, "color");
		render->SetUniform(uniformAlpha, "a");
		render->SetUniform(uniformAffectedLight, "affectedLight");
		render->SetUniform(uniformBaseTexture, "baseTexture");
		render->SetUniform(uniformUseTexture, "useTexture");
	}

	void Entity3D::NodeDraw()
	{
		UpdateShader();
		
		if (textures.size() > 0)
		{
			render->UpdateTexture(uniformBaseTexture, textures[0].id);
		}

		if (material != nullptr)
		{
			material->UpdateShader();
		}

		for (int i = 0; i < textures.size(); i++)
		{
			render->UseTexture(i, textures[i].id);
		}

		if (canDraw)
		{
			render->Draw(VAO, indexes.size());
		}

		render->CleanTexture();
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->NodeDraw();
		}
	}

	void Entity3D::UpdateShader()
	{
		Entity::UpdateShader();
		render->UpdateColor(uniformColor, uniformAlpha, color.GetColor());
		render->UpdateStatus(uniformAffectedLight, affectedLight);
		render->UpdateStatus(uniformUseTexture, true);
	}
}