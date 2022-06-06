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
		meshes = ModelImporter::LoadModel(render, path);

		SetUniforms(render->GetTextureShaderId());
	}

	void Entity3D::Draw()
	{
		render->BlendEnable();
		render->UseShader(render->GetTextureShaderId());
		UpdateShader();
		
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}

		render->TextureDisable();
		render->CleanShader();
		render->BlendDisable();
	}
	
	void Entity3D::SetUniforms(uint shaderId)
	{
		Entity::SetUniforms(shaderId);
		render->SetUniform(shaderId, uniformAffectedLight, "affectedLight");
	}

	void Entity3D::UpdateShader()
	{
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		render->UpdateStatus(uniformAffectedLight, affectedLight);

		if (material != nullptr)
		{
			material->UpdateShader();
		}
	}
}