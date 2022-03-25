#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "exports.h"
#include "Light/light.h"

namespace GL
{
	class GRAPHICSENGINE_API PointLight : public Light
	{
	public:
		PointLight(Render* render);
		~PointLight();

		void Init() override;
		void UseLight() override;

		void SetConstant(float constant);
		void SetLinear(float linear);
		void SetQuadratic(float quadratic);

		float GetConstant();
		float GetLinear();
		float GetQuadratic();

	private:
		float constant;
		float linear;
		float quadratic;

		uint uniformConstant;
		uint uniformLinear;
		uint uniformQuadratic;
	};
}

#endif // !POINT_LIGHT_H
