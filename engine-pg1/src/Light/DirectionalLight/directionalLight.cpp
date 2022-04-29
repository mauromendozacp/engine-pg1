#include "directionalLight.h"

namespace GL
{
	DirectionalLight::DirectionalLight(Render* render) : Light(render)
	{
		direction = glm::vec3(0.f);
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::UseLight(uint shaderId)
	{
		render->UseShader(shaderId);
		render->UpdateLightVec3(shaderId, color.GetColorRGB(), "directionalLight.color");
		render->UpdateLightVec3(shaderId, direction, "directionalLight.direction");
		render->UpdateLightVec3(shaderId, ambient, "directionalLight.ambient");
		render->UpdateLightVec3(shaderId, diffuse, "directionalLight.diffuse");
		render->UpdateLightVec3(shaderId, specular, "directionalLight.specular");
		render->UpdateLightStatus(shaderId, enabled, "directionalLight.enabled");
		render->CleanShader();
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	glm::vec3 DirectionalLight::GetDirection()
	{
		return direction;
	}
}