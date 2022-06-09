#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "Light/PointLight/pointLight.h"

namespace GL
{
	class GRAPHICSENGINE_API SpotLight : public PointLight
	{
	public:
		SpotLight(Render* render);
		~SpotLight();

		void UseLight(uint shaderId, int index) override;

		void SetDirection(glm::vec3 direction);
		void SetCutOff(float cutOff);
		void SetOuterCutOff(float outerCutOff);

		glm::vec3 GetDirection();
		float GetCutOff();
		float GetOuterCutOff();

	private:
		glm::vec3 direction;
		float cutOff;
		float outerCutOff;
	};
}

#endif // !SPOT_LIGHT_H
