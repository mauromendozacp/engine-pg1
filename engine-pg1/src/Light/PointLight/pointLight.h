#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "exports.h"
#include <string>
#include "Light/light.h"

namespace GL
{
	class GRAPHICSENGINE_API PointLight : public Light
	{
	public:
		PointLight(Render* render);
		~PointLight();

		virtual void Init(int index);
		virtual void UseLight() override;

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

		uint uniformConstant;
		uint uniformLinear;
		uint uniformQuadratic;
	};
}

#endif // !POINT_LIGHT_H