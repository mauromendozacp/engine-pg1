#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D() : Entity()
	{
		meshes = std::vector<Mesh*>();

		uniformAffectedLight = 0;

		affectedLight = true;
		drawVolume = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = glm::vec3(std::numeric_limits<float>::min());
	}

	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		meshes = std::vector<Mesh*>();

		uniformAffectedLight = 0;

		affectedLight = true;
		drawVolume = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = glm::vec3(std::numeric_limits<float>::min());
	}

	Entity3D::Entity3D(std::vector<Mesh*> meshes, Render* render) : Entity(render)
	{
		this->meshes = meshes;

		uniformAffectedLight = 0;

		affectedLight = true;
		drawVolume = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = glm::vec3(std::numeric_limits<float>::min());
	}

	Entity3D::~Entity3D()
	{
	}

	void Entity3D::Init()
	{
		SetUniforms();

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Init();
		}

		volume = new VolumeAABB();
		GenerateVolumeAABB();
		volume->Init(render);
	}

	void Entity3D::Draw()
	{
		if (CheckVolume())
		{
			if (volume != nullptr && drawVolume)
			{
				volume->Draw();
			}

			render->UseShader();
			render->BlendEnable();
			render->TextureEnable();
			UpdateShader();

			for (int i = 0; i < meshes.size(); i++)
			{
				meshes[i]->Draw();
			}

			render->TextureDisable();
			render->BlendDisable();
			render->CleanShader();
		}

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->Draw();
		}
	}

	void Entity3D::DeInit()
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->DeInit();
		}

		for (std::list<Entity*>::iterator it = nodes.begin(); it != nodes.end(); ++it)
		{
			Entity3D* node3d = static_cast<Entity3D*>((*it));
			node3d->DeInit();
		}
	}

	void Entity3D::CanDrawVolume(bool status)
	{
		drawVolume = status;
	}

	bool Entity3D::IsCanDrawVolume()
	{
		return drawVolume;
	}

	void Entity3D::GenerateVolumeAABB()
	{
		if (meshes.size() > 0)
		{
			for (int i = 0; i < meshes.size(); i++)
			{
				Mesh* mesh = meshes[i];
				for (int j = 0; j < mesh->GetVertexs().size(); j++)
				{
					Vertex vertex = mesh->GetVertexs()[j];

					minAABB.x = glm::min(minAABB.x, vertex.Position.x);
					minAABB.y = glm::min(minAABB.y, vertex.Position.y);
					minAABB.z = glm::min(minAABB.z, vertex.Position.z);

					maxAABB.x = glm::max(maxAABB.x, vertex.Position.x);
					maxAABB.y = glm::max(maxAABB.y, vertex.Position.y);
					maxAABB.z = glm::max(maxAABB.z, vertex.Position.z);
				}
			}
			volume->SetVolumeMinMax(minAABB, maxAABB);
		}

		if (parent != nullptr)
		{
			Entity3D* parent3d = static_cast<Entity3D*>(parent);
			parent3d->minAABB = glm::min(minAABB, parent3d->minAABB);
			parent3d->maxAABB = glm::max(maxAABB, parent3d->maxAABB);
		}
	}
	
	void Entity3D::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformAffectedLight, "affectedLight");
	}

	void Entity3D::UpdateShader()
	{
		Entity::UpdateShader();
		render->UpdateStatus(uniformAffectedLight, affectedLight);
	}
}