#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light/light.h"

namespace GL
{
	class GRAPHICSENGINE_API DirectionalLight : public Light
	{
	public:
		DirectionalLight(Render* render);
		~DirectionalLight();
		
		void UseLight(uint shaderId);

		void SetDirection(glm::vec3 direction);
		glm::vec3 GetDirection();

	private:
		glm::vec3 direction;
	};
}

#endif // !DIRECTIONAL_LIGHT_H
