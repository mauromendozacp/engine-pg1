#ifndef MATERIAL_H
#define MATERIAL_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Material
	{
	public:
		Material(Render* render);
		~Material();

		void Init(uint shaderId);
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
