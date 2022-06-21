#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D() : Entity()
	{
		material = nullptr;
		color = Color();

		mesh = Mesh();

		VAO = 0;
		VBO = 0;
		EBO = 0;

		uniformColor = 0;
		uniformAlpha = 0;
		uniformAffectedLight = 0;
		uniformUseTexture = 0;
		uniformBaseTexture = 0;

		affectedLight = true;
	}

	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		material = nullptr;
		color = Color();

		mesh = Mesh();

		VAO = 0;
		VBO = 0;
		EBO = 0;

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
		if (mesh.vertexs.size() == 0)
		{
			render->BindBuffer(VAO, VBO, mesh.vertexs.size() * sizeof(Vertex), 0);
		}
		else
		{
			render->BindBuffer(VAO, VBO, mesh.vertexs.size() * sizeof(Vertex), &mesh.vertexs[0]);
		}

		if (mesh.indexes.size() == 0)
		{
			render->BindIndexs(EBO, mesh.indexes.size() * sizeof(unsigned int), 0);
		}
		else
		{
			render->BindIndexs(EBO, mesh.indexes.size() * sizeof(unsigned int), &mesh.indexes[0]);
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

		if (mesh.textures.size() > 0)
		{
			//render->TextureDelete(uniformBaseTexture, mesh.textures[0].id);
		}

		mesh.vertexs.clear();
		mesh.indexes.clear();
		mesh.textures.clear();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->DeInit();
		}
	}

	void Entity3D::SetMesh(Mesh mesh)
	{
		this->mesh = mesh;
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
		
		if (mesh.textures.size() > 0)
		{
			render->UpdateTexture(uniformBaseTexture, mesh.textures[0].id);
		}

		if (material != nullptr)
		{
			material->UpdateShader();
		}

		for (int i = 0; i < mesh.textures.size(); i++)
		{
			render->UseTexture(i, mesh.textures[i].id);
		}

		if (canDraw)
		{
			render->Draw(VAO, mesh.indexes.size());
		}

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