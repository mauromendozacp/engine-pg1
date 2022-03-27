#include "material.h"

namespace GL
{
	Material::Material()
	{
		shininess = 0.f;
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);

		uniformShininess = 0;
		uniformAmbient = 0;
		uniformDiffuse = 0;
		uniformSpecular = 0;
	}

	Material::~Material()
	{
	}

	void Material::Init(Render* render)
	{
		render->SetUniform(uniformShininess, "material.shininess");
		render->SetUniform(uniformAmbient, "material.ambient");
		render->SetUniform(uniformDiffuse, "material.diffuse");
		render->SetUniform(uniformSpecular, "material.specular");
	}

	void Material::SetShininess(float shininess)
	{
		this->shininess = shininess;
	}

	void Material::SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}

	void Material::SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}

	void Material::SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}

	float Material::GetShininess()
	{
		return shininess;
	}

	glm::vec3 Material::GetAmbient()
	{
		return ambient;
	}

	glm::vec3 Material::GetDiffuse()
	{
		return diffuse;
	}

	glm::vec3 Material::GetSpecular()
	{
		return specular;
	}
}