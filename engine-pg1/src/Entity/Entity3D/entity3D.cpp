#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		material = nullptr;

		uniformAffectedLight = 0;

		affectedLight = true;
	}

	Entity3D::~Entity3D()
	{
	}

	void Entity3D::Init(std::string path)
	{
		ModelImporter* importer = new ModelImporter();
		importer->LoadModel(render, path);

		Mesh* meshBase = importer->GetMeshBase();

		name = meshBase->GetName();
		vertexs = meshBase->GetVertexs();
		indexes = meshBase->GetIndexes();
		textures = meshBase->GetTextures();

		VAO = meshBase->GetVAO();
		VBO = meshBase->GetVBO();
		EBO = meshBase->GetEBO();

		for (int i = 0; i < meshBase->GetMeshSons().size(); i++)
		{
			Entity3D* node = new Entity3D(render);
			node->SetParent(this);

			node->SetMeshData(meshBase->GetMeshSons()[i], node);
			node->SetUniforms(render->GetTextureShaderId());

			nodes.push_back(node);
		}

		SetUniforms(render->GetTextureShaderId());

		delete importer;
	}

	void Entity3D::Draw()
	{
		render->BlendEnable();

		

		NodeDraw();

		
		render->BlendDisable();
	}

	void Entity3D::DeInit()
	{
		NodeDeInit();
	}
	
	void Entity3D::SetUniforms(uint shaderId)
	{
		Entity::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformAffectedLight, "affectedLight");
	}

	void Entity3D::SetMeshData(Mesh* mesh, Entity3D* parent)
	{
		name = mesh->GetName();
		vertexs = mesh->GetVertexs();
		indexes = mesh->GetIndexes();
		textures = mesh->GetTextures();

		VAO = mesh->GetVAO();
		VBO = mesh->GetVBO();
		EBO = mesh->GetEBO();

		for (int i = 0; i < mesh->GetMeshSons().size(); i++)
		{
			Entity3D* node = new Entity3D(render);
			node->SetParent(parent);

			node->SetMeshData(mesh->GetMeshSons()[i], node);
			node->SetUniforms(render->GetTextureShaderId());

			nodes.push_back(node);
		}
	}

	void Entity3D::NodeDraw()
	{
		render->UseShader(render->GetTextureShaderId());
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		render->UpdateStatus(uniformAffectedLight, affectedLight);

		if (material != nullptr)
		{
			material->UpdateShader();
		}

		render->TextureEnable();

		for (int i = 0; i < textures.size(); i++)
		{
			render->UseTexture(i, textures[i].id);
			render->UpdateMaterialValue(render->GetTextureShaderId(), i, ("material." + textures[i].type).c_str());
		}

		render->DrawMesh(VAO, indexes.size());
		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->NodeDraw();
		}

		render->TextureDisable();
		render->CleanShader();
	}

	void Entity3D::NodeDeInit()
	{
		render->UnBind(VAO, VBO, EBO);

		vertexs.clear();
		indexes.clear();
		textures.clear();

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->NodeDeInit();
		}
	}

	std::vector<Vertex> Entity3D::GetVertexs()
	{
		return vertexs;
	}

	std::vector<uint> Entity3D::GetIndexes()
	{
		return indexes;
	}

	std::vector<Texture> Entity3D::GetTextures()
	{
		return textures;
	}

	uint Entity3D::GetVAO()
	{
		return VAO;
	}

	uint Entity3D::GetVBO()
	{
		return VBO	;
	}

	uint Entity3D::GetEBO()
	{
		return EBO;
	}
}