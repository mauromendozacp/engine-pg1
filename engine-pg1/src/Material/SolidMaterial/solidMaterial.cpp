#include "solidMaterial.h"

namespace GL
{
	SolidMaterial::SolidMaterial(Render* render) : Material(render)
	{
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);

		uniformAmbient = 0;
	}

	SolidMaterial::~SolidMaterial()
	{
	}

	void SolidMaterial::Init(uint shaderId)
	{
		render->SetUniform(shaderId, uniformAmbient, "material.ambient");
		Material::Init(shaderId);
	}

	void SolidMaterial::UpdateShader()
	{
		render->UpdateVec3(uniformAmbient, ambient);
		render->UpdateVec3(uniformDiffuse, diffuse);
		render->UpdateVec3(uniformSpecular, specular);
		Material::UpdateShader();
	}

	void SolidMaterial::SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}

	void SolidMaterial::SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}

	void SolidMaterial::SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}

	glm::vec3 SolidMaterial::GetAmbient()
	{
		return ambient;
	}

	glm::vec3 SolidMaterial::GetDiffuse()
	{
		return diffuse;
	}

	glm::vec3 SolidMaterial::GetSpecular()
	{
		return specular;
	}
}