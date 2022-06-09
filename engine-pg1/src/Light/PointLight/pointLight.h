#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "Light/light.h"

#include <string>

namespace GL
{
	class GRAPHICSENGINE_API PointLight : public Light
	{
	public:
		PointLight(Render* render);
		~PointLight();

		virtual void UseLight(uint shaderId, int index);

		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);

		float GetConstant();
		float GetLinear();
		float GetQuadratic();

	protected:
		float constant;
		float linear;
		float quadratic;
	};
}

#endif // !POINT_LIGHT_H
