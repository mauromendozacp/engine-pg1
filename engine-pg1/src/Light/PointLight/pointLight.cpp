#include "pointLight.h"

namespace GL
{
	PointLight::PointLight(Render* render) : Light(render)
	{
		constant = 0.f;
		linear = 0.f;
		quadratic = 0.f;

		uniformConstant = 0;
		uniformLinear = 0;
		uniformQuadratic = 0;
	}

	PointLight::~PointLight()
	{
	}

	void PointLight::UseLight()
	{
		Light::UseLight();
		render->UpdateLightVec3(uniformPosition, transform.position);
		render->UpdateLightFloat(uniformConstant, constant);
		render->UpdateLightFloat(uniformLinear, linear);
		render->UpdateLightFloat(uniformQuadratic, quadratic);
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

	void PointLight::SetUniforms(int index)
	{
		std::string indexSTR = std::to_string(index).c_str();
		render->SetUniform(uniformColor, ("pointLight[" + indexSTR + "].color").c_str());
		render->SetUniform(uniformPosition, ("pointLight[" + indexSTR + "].position").c_str());
		render->SetUniform(uniformAmbient, ("pointLight[" + indexSTR + "].ambient").c_str());
		render->SetUniform(uniformDiffuse, ("pointLight[" + indexSTR + "].diffuse").c_str());
		render->SetUniform(uniformSpecular, ("pointLight[" + indexSTR + "].specular").c_str());
		render->SetUniform(uniformConstant, ("pointLight[" + indexSTR + "].constant").c_str());
		render->SetUniform(uniformLinear, ("pointLight[" + indexSTR + "].linear").c_str());
		render->SetUniform(uniformQuadratic, ("pointLight[" + indexSTR + "].quadratic").c_str());
		render->SetUniform(uniformEnabled, ("pointLight[" + indexSTR + "].enabled").c_str());
	}
}