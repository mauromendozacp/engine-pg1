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
		maxAABB = -glm::vec3(std::numeric_limits<float>::max());
	}

	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		meshes = std::vector<Mesh*>();

		uniformAffectedLight = 0;

		affectedLight = true;
		drawVolume = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = -glm::vec3(std::numeric_limits<float>::max());
	}

	Entity3D::Entity3D(std::vector<Mesh*> meshes, Render* render) : Entity(render)
	{
		this->meshes = meshes;

		uniformAffectedLight = 0;

		affectedLight = true;
		drawVolume = false;

		minAABB = glm::vec3(std::numeric_limits<float>::max());
		maxAABB = -glm::vec3(std::numeric_limits<float>::max());
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

		GenerateVolumeAABB();
	}

	void Entity3D::Draw()
	{
		if (IsCanDraw())
		{
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

			Entity::Draw();
		}
	}

	void Entity3D::DeInit()
	{
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->DeInit();
		}

		Entity::DeInit();
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
		}

		localVolume = new VolumeAABB(minAABB, maxAABB);
		globalVolume = new VolumeAABB();
		globalVolume->SetGlobalVolume(localVolume, matrix.model);
		globalVolume->Init(render);

		if (parent != nullptr)
		{
			Entity3D* parent3d = static_cast<Entity3D*>(parent);

			parent3d->minAABB.x = glm::min(minAABB.x, parent3d->minAABB.x);
			parent3d->minAABB.y = glm::min(minAABB.y, parent3d->minAABB.y);
			parent3d->minAABB.z = glm::min(minAABB.z, parent3d->minAABB.z);

			parent3d->maxAABB.x = glm::max(maxAABB.x, parent3d->maxAABB.x);
			parent3d->maxAABB.y = glm::max(maxAABB.y, parent3d->maxAABB.y);
			parent3d->maxAABB.z = glm::max(maxAABB.z, parent3d->maxAABB.z);
		}
	}
}