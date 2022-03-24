#include "light.h"

namespace GL
{
	Light::Light(Render* render) : Entity(render)
	{
		color = glm::vec3(0.f);
		direction = glm::vec3(0.f);
		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);

		uniformColor = 0;
		uniformPosition = 0;
		uniformDirection = 0;
		uniformAmbient = 0;
		uniformDiffuse = 0;
		uniformSpecular = 0;
	}

	Light::~Light()
	{
	}

	void Light::Init()
	{
		render->SetUniform(render->GetSolidShaderId(), uniformColor, "lightColor");
	}

	void Light::UseLight()
	{
		render->UseShaderId(render->GetSolidShaderId());
		render->UpdateLight(color, uniformColor);
		render->CleanShaderId();
	}

	void Light::SetColor(glm::vec3 color)
	{
		this->color = color;
	}

	void Light::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	void Light::SetAmbient(glm::vec3 ambient)
	{
		this->ambient = ambient;
	}

	void Light::SetDiffuse(glm::vec3 diffuse)
	{
		this->diffuse = diffuse;
	}

	void Light::SetSpecular(glm::vec3 specular)
	{
		this->specular = specular;
	}

	glm::vec3 Light::GetColor()
	{
		return color;
	}
	glm::vec3 Light::GetDirection()
	{
		return direction;
	}
	glm::vec3 Light::GetAmbient()
	{
		return ambient;
	}
	glm::vec3 Light::GetDiffuse()
	{
		return diffuse;
	}
	glm::vec3 Light::GetSpecular()
	{
		return specular;
	}
}