#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D() : Entity()
	{
		meshes = std::vector<Mesh*>();

		uniformAffectedLight = 0;

		affectedLight = true;
	}

	Entity3D::Entity3D(Render* render) : Entity(render)
	{
		meshes = std::vector<Mesh*>();

		uniformAffectedLight = 0;

		affectedLight = true;
	}

	Entity3D::Entity3D(std::vector<Mesh*> meshes, Render* render) : Entity(render)
	{
		this->meshes = meshes;

		uniformAffectedLight = 0;

		affectedLight = true;
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
	
	void Entity3D::SetUniforms()
	{
		Entity::SetUniforms();
		render->SetUniform(uniformAffectedLight, "affectedLight");
	}

	void Entity3D::NodeDraw()
	{
		if (true)
		//if (CheckVolume())
		{
			UpdateShader();

			for (int i = 0; i < meshes.size(); i++)
			{
				meshes[i]->Draw();
			}
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
		render->UpdateStatus(uniformAffectedLight, affectedLight);
	}
}