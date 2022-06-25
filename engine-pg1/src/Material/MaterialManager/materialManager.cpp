#include "materialManager.h"

namespace GL
{
	SolidMaterial* MaterialManager::solidMaterial = nullptr;
	TextureMaterial* MaterialManager::textureMaterial = nullptr;

	MaterialManager::MaterialManager()
	{
		solidMaterial = nullptr;
		textureMaterial = nullptr;
	}

	MaterialManager::~MaterialManager()
	{
	}

	void MaterialManager::Init(Render* render)
	{
		solidMaterial = new SolidMaterial(render);
		solidMaterial->Init();
		solidMaterial->SetAmbient(glm::vec3(0.5f, 0.5f, 0.5f));
		solidMaterial->SetDiffuse(glm::vec3(0.4f, 0.4f, 0.4f));
		solidMaterial->SetSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		solidMaterial->SetShininess(64.f);

		textureMaterial = new TextureMaterial(render);
		textureMaterial->Init();
		textureMaterial->SetDiffuse(0);
		textureMaterial->SetSpecular(1);
		textureMaterial->SetShininess(64.f);
	}

	void MaterialManager::DeInit()
	{
		if (solidMaterial != nullptr)
		{
			delete solidMaterial;
			solidMaterial = nullptr;
		}
		if (textureMaterial != nullptr)
		{
			delete textureMaterial;
			textureMaterial = nullptr;
		}
	}

	void MaterialManager::SetSolidMaterial(SolidMaterial* solidMat)
	{
		solidMaterial = solidMat;
	}

	void MaterialManager::SetTextureMaterial(TextureMaterial* textureMat)
	{
		textureMaterial = textureMat;
	}

	SolidMaterial* MaterialManager::GetSolidMaterial()
	{
		return solidMaterial;
	}

	TextureMaterial* MaterialManager::GetTextureMaterial()
	{
		return textureMaterial;
	}
}