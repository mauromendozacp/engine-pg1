#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "exports.h"
#include "PointLight/pointLight.h"

namespace GL
{
	class GRAPHICSENGINE_API SpotLight : public PointLight
	{
	public:
		SpotLight(Render* render);
		~SpotLight();

		void Init() override;
		void UseLight() override;

		void SetCutOff(float cutOff);
		float GetCutOff();

	private:
		float cutOff;

		uint uniformCutOff;
	};
}

#endif // !SPOT_LIGHT_H
