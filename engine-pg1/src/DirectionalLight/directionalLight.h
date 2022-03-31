#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "exports.h"
#include "Light/light.h"

namespace GL
{
	class GRAPHICSENGINE_API DirectionalLight : public Light
	{
	public:
		DirectionalLight(Render* render);
		~DirectionalLight();
		
		void Init() override;
		void UseLight() override;

		void SetDirection(glm::vec3 direction);
		glm::vec3 GetDirection();

	private:
		glm::vec3 direction;

		uint uniformDirection;
	};
}

#endif // !DIRECTIONAL_LIGHT_H
