#include "spotLight.h"

namespace GL
{
	SpotLight::SpotLight(Render* render) : PointLight(render)
	{
		direction = glm::vec3(0.f);
		cutOff = 0.f;
		outerCutOff = 0.f;

		uniformDirection = 0;
		uniformCutOff = 0;
		uniformOuterCutOff = 0;
	}

	SpotLight::~SpotLight()
	{
	}

	void SpotLight::Init()
	{
		render->SetUniform(uniformColor, "spotLight.pointLight.color");
		render->SetUniform(uniformPosition, "spotLight.pointLight.position");
		render->SetUniform(uniformAmbient, "spotLight.pointLight.ambient");
		render->SetUniform(uniformDiffuse, "spotLight.pointLight.diffuse");
		render->SetUniform(uniformSpecular, "spotLight.pointLight.specular");
		render->SetUniform(uniformConstant, "spotLight.pointLight.constant");
		render->SetUniform(uniformLinear, "spotLight.pointLight.linear");
		render->SetUniform(uniformQuadratic, "spotLight.pointLight.quadratic");
		render->SetUniform(uniformDirection, "spotLight.direction");
		render->SetUniform(uniformCutOff, "spotLight.cutOff");
		render->SetUniform(uniformOuterCutOff, "spotLight.outerCutOff");
		render->SetUniform(uniformEnabled, "spotLight.enabled");
	}

	void SpotLight::UseLight()
	{
		render->UseShader();
		render->UpdateLight(uniformColor, color.GetColorRGB());
		render->UpdateLight(uniformDirection, direction);
		render->UpdateLight(uniformPosition, transform.position);
		render->UpdateLight(uniformAmbient, ambient);
		render->UpdateLight(uniformDiffuse, diffuse);
		render->UpdateLight(uniformSpecular, specular);
		render->UpdateFloatValue(uniformConstant, constant);
		render->UpdateFloatValue(uniformLinear, linear);
		render->UpdateFloatValue(uniformQuadratic, quadratic);
		render->UpdateFloatValue(uniformCutOff, cutOff);
		render->UpdateFloatValue(uniformOuterCutOff, outerCutOff);
		render->UpdateStatus(uniformEnabled, enabled);
		render->CleanShader();
	}

	void SpotLight::SetDirection(glm::vec3 direction)
	{
		this->direction = direction;
	}

	void SpotLight::SetCutOff(float cutOff)
	{
		this->cutOff = cos(glm::radians(cutOff));
	}

	void SpotLight::SetOuterCutOff(float outerCutOff)
	{
		this->outerCutOff = cos(glm::radians(outerCutOff));
	}

	glm::vec3 SpotLight::GetDirection()
	{
		return direction;
	}

	float SpotLight::GetCutOff()
	{
		return cutOff;
	}

	float SpotLight::GetOuterCutOff()
	{
		return outerCutOff;
	}
}