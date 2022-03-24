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
		render->UpdateLight(color, uniformColor);
		render->UpdateLight(direction, uniformDirection);
		render->UpdateLight(ambient, uniformAmbient);
		render->UpdateLight(diffuse, uniformDiffuse);
		render->UpdateLight(specular, uniformSpecular);
		render->UpdateStatus(enabled, uniformEnabled);
		render->CleanShader();
	}
}