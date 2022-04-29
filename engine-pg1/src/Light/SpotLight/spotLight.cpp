#include "spotLight.h"

namespace GL
{
	SpotLight::SpotLight(Render* render) : PointLight(render)
	{
		direction = glm::vec3(0.f);
		cutOff = 0.f;
		outerCutOff = 0.f;
	}

	SpotLight::~SpotLight()
	{
	}

	void SpotLight::UseLight(uint shaderId, int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		render->UseShader(shaderId);
		render->UpdateLightVec3(shaderId, color.GetColorRGB(), ("spotLight[" + indexSTR + "].pointLight.color").c_str());
		render->UpdateLightVec3(shaderId, direction, ("spotLight[" + indexSTR + "].direction").c_str());
		render->UpdateLightVec3(shaderId, transform.position, ("spotLight[" + indexSTR + "].pointLight.position").c_str());
		render->UpdateLightVec3(shaderId, ambient, ("spotLight[" + indexSTR + "].pointLight.ambient").c_str());
		render->UpdateLightVec3(shaderId, diffuse, ("spotLight[" + indexSTR + "].pointLight.diffuse").c_str());
		render->UpdateLightVec3(shaderId, specular, ("spotLight[" + indexSTR + "].pointLight.specular").c_str());
		render->UpdateLightFloat(shaderId, constant, ("spotLight[" + indexSTR + "].pointLight.constant").c_str());
		render->UpdateLightFloat(shaderId, linear, ("spotLight[" + indexSTR + "].pointLight.linear").c_str());
		render->UpdateLightFloat(shaderId, quadratic, ("spotLight[" + indexSTR + "].pointLight.quadratic").c_str());
		render->UpdateLightFloat(shaderId, cutOff, ("spotLight[" + indexSTR + "].cutOff").c_str());
		render->UpdateLightFloat(shaderId, outerCutOff, ("spotLight[" + indexSTR + "].outerCutOff").c_str());
		render->UpdateLightStatus(shaderId, enabled, ("spotLight[" + indexSTR + "].enabled").c_str());
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