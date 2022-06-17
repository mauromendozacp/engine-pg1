#ifndef MATERIAL_H
#define MATERIAL_H

#include "exports.h"

#include "Renderer/renderer.h"

#include "GLM/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Material
	{
	public:
		Material(Render* render);
		~Material();

		virtual void Init() = 0;
		virtual void UpdateShader();

		void SetShininess(float shininess);
		float GetShininess();

	protected:
		Render* render;

		float shininess;

		uint uniformDiffuse;
		uint uniformSpecular;
		uint uniformShininess;
	};
}

#endif // !MATERIAL_H
