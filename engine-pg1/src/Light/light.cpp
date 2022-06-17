#include "light.h"

namespace GL
{
	Light::Light(Render* render) : Entity(render)
	{
		color = Color();

		ambient = glm::vec3(0.f);
		diffuse = glm::vec3(0.f);
		specular = glm::vec3(0.f);
		enabled = true;

		uniformColor = 0;
		uniformAmbient = 0;
		uniformDiffuse = 0;
		uniformSpecular = 0;
		uniformEnabled = 0;
	}

	Light::~Light()
	{
	}

	void Light::UseLight()
	{
		render->UpdateMVP(uniformModel, uniformView, uniformProjection, matrix.model);
		render->UpdateLightVec3(uniformColor, color.GetColorRGB());
		render->UpdateLightVec3(uniformAmbient, ambient);
		render->UpdateLightVec3(uniformDiffuse, diffuse);
		render->UpdateLightVec3(uniformSpecular, specular);
		render->UpdateLightStatus(uniformEnabled, enabled);
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