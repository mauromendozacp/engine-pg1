#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

#include "exports.h"
#include "Light/DirectionalLight/directionalLight.h"
#include "Light/PointLight/pointLight.h"
#include "Light/SpotLight/spotLight.h"

namespace GL
{
	int const lightMax = 3;

	enum class LIGHT_TYPE
	{
		DIRECTIONAL,
		POINTLIGHT,
		SPOTLIGHT
	};

	class GRAPHICSENGINE_API LightManager
	{
	public:
		LightManager(Render* render);
		~LightManager();

		void AddLight(LIGHT_TYPE type);
		void UseLights();

		DirectionalLight* GetDirectionalLight();
		PointLight* GetPointLight(int index);
		SpotLight* GetSpotLight(int index);
		PointLight* GetLasPointLightCreated();
		SpotLight* GetLasSpotLightCreated();

	private:
		Render* render;
		int pointLightsCreated;
		int spotLightsCreated;

		DirectionalLight* directionalLight;
		PointLight* pointLights[lightMax];
		SpotLight* spotLights[lightMax];
	};
}

#endif // !LIGHT_MANAGER_H
