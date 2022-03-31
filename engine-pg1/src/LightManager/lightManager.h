#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "exports.h"
#include "DirectionalLight/directionalLight.h"
#include "PointLight/pointLight.h"
#include "SpotLight/spotLight.h"

namespace GL
{
	int const lightMax = 3;

	class GRAPHICSENGINE_API LightManager
	{
	public:
		LightManager();
		~LightManager();

		void Init(Render* render);
		void UseLights();

		DirectionalLight* GetDirectionalLight();
		PointLight* GetPointLight(int index);
		SpotLight* GetSpotLight(int index);

	private:
		DirectionalLight* directionalLight;
		PointLight* pointLights[lightMax];
		SpotLight* spotLights[lightMax];
	};
}

#endif // !LIGHT_MANAGER_H
