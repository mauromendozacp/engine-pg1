#include "entity3D.h"

namespace GL
{
	Entity3D::Entity3D(Render* render) : Entity(render)
	{
	}

	Entity3D::~Entity3D()
	{
	}

	void Entity3D::Init(std::string path)
	{
		meshes = ModelImporter::LoadModel(render, path);
	}

	void Entity3D::Draw()
	{
		render->UseShader(render->GetTextureShaderId());
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		
		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i].Draw();
		}
	}
}