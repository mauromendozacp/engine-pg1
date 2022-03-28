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

	void PointLight::Init()
	{
		render->SetUniform(uniformColor, "pointLight.color");
		render->SetUniform(uniformPosition, "pointLight.position");
		render->SetUniform(uniformAmbient, "pointLight.ambient");
		render->SetUniform(uniformDiffuse, "pointLight.diffuse");
		render->SetUniform(uniformSpecular, "pointLight.specular");
		render->SetUniform(uniformConstant, "pointLight.constant");
		render->SetUniform(uniformLinear, "pointLight.linear");
		render->SetUniform(uniformQuadratic, "pointLight.quadratic");
		render->SetUniform(uniformEnabled, "pointLight.enabled");
	}

	void PointLight::UseLight()
	{
		render->UseShader();
		render->UpdateLight(uniformColor, color.GetColorRGB());
		render->UpdateLight(uniformPosition, transform.position);
		render->UpdateLight(uniformAmbient, ambient);
		render->UpdateLight(uniformDiffuse, diffuse);
		render->UpdateLight(uniformSpecular, specular);
		render->UpdateFloatValue(uniformConstant, constant);
		render->UpdateFloatValue(uniformLinear, linear);
		render->UpdateFloatValue(uniformQuadratic, quadratic);
		render->UpdateStatus(uniformEnabled, enabled);
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