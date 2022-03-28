#include "spotLight.h"

namespace GL
{
	SpotLight::SpotLight(Render* render) : PointLight(render)
	{
		cutOff = 0.f;
		uniformCutOff = 0;
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
		render->SetUniform(uniformEnabled, "spotLight.enabled");
	}

	void SpotLight::UseLight()
	{
		render->UseShader();
		render->UpdateLight(color, uniformColor);
		render->UpdateLight(direction, uniformDirection);
		render->UpdateLight(transform.position, uniformPosition);
		render->UpdateLight(ambient, uniformAmbient);
		render->UpdateLight(diffuse, uniformDiffuse);
		render->UpdateLight(specular, uniformSpecular);
		render->UpdateFloatValue(constant, uniformConstant);
		render->UpdateFloatValue(linear, uniformLinear);
		render->UpdateFloatValue(quadratic, uniformQuadratic);
		render->UpdateFloatValue(cutOff, uniformCutOff);
		render->UpdateStatus(uniformEnabled, enabled);
		render->CleanShader();
	}

	void SpotLight::SetCutOff(float cutOff)
	{
		this->cutOff = cos(glm::radians(cutOff));
	}

	float SpotLight::GetCutOff()
	{
		return cutOff;
	}
}