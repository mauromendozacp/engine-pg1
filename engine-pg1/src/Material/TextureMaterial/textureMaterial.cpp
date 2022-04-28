#include "textureMaterial.h"

namespace GL
{
	TextureMaterial::TextureMaterial(Render* render) : Material(render)
	{
		diffuse = 0;
		specular = 0;
	}

	TextureMaterial::~TextureMaterial()
	{
	}

	void TextureMaterial::Init()
	{
		Material::Init();
	}

	void TextureMaterial::UpdateShader()
	{
		render->UpdateIntValue(uniformDiffuse, diffuse);
		render->UpdateIntValue(uniformSpecular, specular);
		Material::UpdateShader();
	}

	void TextureMaterial::SetDiffuse(uint diffuse)
	{
		this->diffuse = diffuse;
	}

	void TextureMaterial::SetSpecular(uint specular)
	{
		this->specular = specular;
	}

	uint TextureMaterial::GetDiffuse()
	{
		return diffuse;
	}

	uint TextureMaterial::GetSpecular()
	{
		return specular;
	}
}