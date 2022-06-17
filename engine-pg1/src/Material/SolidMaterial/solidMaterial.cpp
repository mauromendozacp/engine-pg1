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

	void SolidMaterial::Init()
	{
		render->SetUniform(uniformAmbient, "baseMaterial.ambient");
		render->SetUniform(uniformDiffuse, "baseMaterial.diffuse");
		render->SetUniform(uniformSpecular, "baseMaterial.specular");
		render->SetUniform(uniformShininess, "baseMaterial.shininess");
	}

	void SolidMaterial::UpdateShader()
	{
		render->UpdateVec3Value(uniformAmbient, ambient);
		render->UpdateVec3Value(uniformDiffuse, diffuse);
		render->UpdateVec3Value(uniformSpecular, specular);
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