#include "directionalLight.h"

namespace GL
{
	DirectionalLight::DirectionalLight(Render* render) : Light(render)
	{
		direction = glm::vec3(0.f);

		uniformDirection = 0;
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::UpdateShader()
	{
		Light::UpdateShader();
		render->UpdateVec3Value(uniformDirection, direction);
	}

	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	glm::vec3 DirectionalLight::GetDirection()
	{
		return direction;
	}

	void DirectionalLight::SetUniforms()
	{
		render->SetUniform(uniformColor, "directionalLight.color");
		render->SetUniform(uniformDirection, "directionalLight.direction");
		render->SetUniform(uniformAmbient, "directionalLight.ambient");
		render->SetUniform(uniformDiffuse, "directionalLight.diffuse");
		render->SetUniform(uniformSpecular, "directionalLight.specular");
		render->SetUniform(uniformEnabled, "directionalLight.enabled");
	}
}