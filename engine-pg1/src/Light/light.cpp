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
		enabled = true;

		uniformColor = 0;
		uniformPosition = 0;
		uniformDirection = 0;
		uniformAmbient = 0;
		uniformDiffuse = 0;
		uniformSpecular = 0;
		uniformEnabled = 0;
	}

	Light::~Light()
	{
	}

	void Light::Init()
	{
		render->SetUniform(uniformColor, "baselight.color");
		render->SetUniform(uniformEnabled, "baselight.enabled");
	}

	void Light::UseLight()
	{
		render->UseShader();
		render->UpdateLight(color, uniformColor);
		render->UpdateStatus(enabled, uniformEnabled);
		render->CleanShader();
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

	void Light::SetEnabled(bool enabled)
	{
		this->enabled = enabled;
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

	bool Light::IsEnabled()
	{
		return enabled;
	}
}