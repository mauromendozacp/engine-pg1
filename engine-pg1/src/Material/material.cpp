#include "material.h"

namespace GL
{
	Material::Material(Render* render)
	{
		this->render = render;

		shininess = 0.f;

		uniformDiffuse = 0;
		uniformSpecular = 0;
		uniformShininess = 0;
	}

	Material::~Material()
	{
	}

	void Material::Init(uint shaderId)
	{
		render->SetUniform(shaderId, uniformDiffuse, "material.diffuse");
		render->SetUniform(shaderId, uniformSpecular, "material.specular");
		render->SetUniform(shaderId, uniformShininess, "material.shininess");
	}

	void Material::UpdateShader()
	{
		render->UpdateFloatValue(uniformShininess, shininess);
	}

	void Material::SetShininess(float shininess)
	{
		this->shininess = shininess;
	}

	float Material::GetShininess()
	{
		return shininess;
	}
}