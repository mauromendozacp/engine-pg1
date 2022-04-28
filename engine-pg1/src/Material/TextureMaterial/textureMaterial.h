#ifndef TEXTURE_MATERIAL_H
#define TEXTURE_MATERIAL_H

#include "Material/material.h"

namespace GL
{
	class GRAPHICSENGINE_API TextureMaterial : public Material
	{
	public:
		TextureMaterial(Render* render);
		~TextureMaterial();

		void Init();
		void UpdateShader();

		void SetDiffuse(uint diffuse);
		void SetSpecular(uint specular);

		uint GetDiffuse();
		uint GetSpecular();

	private:
		uint diffuse;
		uint specular;
	};
}

#endif // !TEXTURE_MATERIAL_H
