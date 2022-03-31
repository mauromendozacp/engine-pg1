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

		uint uniformDirection;
		uint uniformCutOff;
		uint uniformOuterCutOff;
	};
}

#endif // !SPOT_LIGHT_H
