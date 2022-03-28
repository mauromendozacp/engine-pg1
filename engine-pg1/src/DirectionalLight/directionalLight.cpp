#include "directionalLight.h"

namespace GL
{
	DirectionalLight::DirectionalLight(Render* render) : Light(render)
	{
	}

	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::Init()
	{
		render->SetUniform(uniformColor, "directionalLight.color");
		render->SetUniform(uniformDirection, "directionalLight.direction");
		render->SetUniform(uniformAmbient, "directionalLight.ambient");
		render->SetUniform(uniformDiffuse, "directionalLight.diffuse");
		render->SetUniform(uniformSpecular, "directionalLight.specular");
		render->SetUniform(uniformEnabled, "directionalLight.enabled");
	}

	void DirectionalLight::UseLight()
	{
		render->UseShader();
		render->UpdateLight(uniformColor, color.GetColorRGB());
		render->UpdateLight(uniformDirection, direction);
		render->UpdateLight(uniformAmbient, ambient);
		render->UpdateLight(uniformDiffuse, diffuse);
		render->UpdateLight(uniformSpecular, specular);
		render->UpdateStatus(uniformEnabled, enabled);
		render->CleanShader();
	}
}