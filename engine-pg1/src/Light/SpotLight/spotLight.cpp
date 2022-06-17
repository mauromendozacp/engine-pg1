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

	void SpotLight::UseLight()
	{
		PointLight::UseLight();
		render->UpdateLightVec3(uniformDirection, direction);
		render->UpdateLightFloat(uniformCutOff, cutOff);
		render->UpdateLightFloat(uniformOuterCutOff, outerCutOff);
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

	void SpotLight::SetUniforms(int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		render->SetUniform(uniformColor, ("spotLight[" + indexSTR + "].pointLight.color").c_str());
		render->SetUniform(uniformDirection, ("spotLight[" + indexSTR + "].direction").c_str());
		render->SetUniform(uniformPosition, ("spotLight[" + indexSTR + "].pointLight.position").c_str());
		render->SetUniform(uniformAmbient, ("spotLight[" + indexSTR + "].pointLight.ambient").c_str());
		render->SetUniform(uniformDiffuse, ("spotLight[" + indexSTR + "].pointLight.diffuse").c_str());
		render->SetUniform(uniformSpecular, ("spotLight[" + indexSTR + "].pointLight.specular").c_str());
		render->SetUniform(uniformConstant, ("spotLight[" + indexSTR + "].pointLight.constant").c_str());
		render->SetUniform(uniformLinear, ("spotLight[" + indexSTR + "].pointLight.linear").c_str());
		render->SetUniform(uniformQuadratic, ("spotLight[" + indexSTR + "].pointLight.quadratic").c_str());
		render->SetUniform(uniformCutOff, ("spotLight[" + indexSTR + "].cutOff").c_str());
		render->SetUniform(uniformOuterCutOff, ("spotLight[" + indexSTR + "].outerCutOff").c_str());
		render->SetUniform(uniformEnabled, ("spotLight[" + indexSTR + "].enabled").c_str());
	}
}