#include "pointLight.h"

namespace GL
{
	PointLight::PointLight(Render* render) : Light(render)
	{
		constant = 0.f;
		linear = 0.f;
		quadratic = 0.f;
	}

	PointLight::~PointLight()
	{
	}

	void PointLight::UseLight(uint shaderId, int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		render->UseShader(shaderId);
		render->UpdateLightVec3(shaderId, color.GetColorRGB(), ("pointLight[" + indexSTR + "].color").c_str());
		render->UpdateLightVec3(shaderId, transform.position, ("pointLight[" + indexSTR + "].position").c_str());
		render->UpdateLightVec3(shaderId, ambient, ("pointLight[" + indexSTR + "].ambient").c_str());
		render->UpdateLightVec3(shaderId, diffuse, ("pointLight[" + indexSTR + "].diffuse").c_str());
		render->UpdateLightVec3(shaderId, specular, ("pointLight[" + indexSTR + "].specular").c_str());
		render->UpdateLightFloat(shaderId, constant, ("pointLight[" + indexSTR + "].constant").c_str());
		render->UpdateLightFloat(shaderId, linear, ("pointLight[" + indexSTR + "].linear").c_str());
		render->UpdateLightFloat(shaderId, quadratic, ("pointLight[" + indexSTR + "].quadratic").c_str());
		render->UpdateLightStatus(shaderId, enabled, ("pointLight[" + indexSTR + "].enabled").c_str());
		render->CleanShader();
	}

	void PointLight::SetConstant(float constant)
	{
		this->constant = constant;
	}

	void PointLight::SetLinear(float linear)
	{
		this->linear = linear;
	}

	void PointLight::SetQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}

	float PointLight::GetConstant()
	{
		return constant;
	}

	float PointLight::GetLinear()
	{
		return linear;
	}

	float PointLight::GetQuadratic()
	{
		return quadratic;
	}
}