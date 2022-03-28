#ifndef COLOR_H
#define COLOR_H

#include "exports.h"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Color
	{
	public:
		Color();
		~Color();

		void SetColor(int r, int g, int b);
		void SetColor(int r, int g, int b, int a);
		void SetColor(float r, float g, float b);
		void SetColor(float r, float g, float b, float a);

		glm::vec4 GetColor();
		glm::vec3 GetColorRGB();

	private:
		float r, g, b, a;
	};
}

#endif // !COLOR_H