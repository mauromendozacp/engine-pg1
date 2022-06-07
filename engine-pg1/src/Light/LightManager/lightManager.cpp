#include "lightManager.h"

namespace GL
{
	LightManager::LightManager(Render* render)
	{
		this->render = render;
		pointLightsCreated = 0;
		spotLightsCreated = 0;

		directionalLight = nullptr;
		for (int i = 0; i < lightMax; i++)
		{
			pointLights[i] = nullptr;
			spotLights[i] = nullptr;
		}
	}

	LightManager::~LightManager()
	{
		if (directionalLight != nullptr)
		{
			delete directionalLight;
			directionalLight = nullptr;
		}
		for (int i = 0; i < lightMax; i++)
		{
			if (pointLights[i] != nullptr)
			{
				delete pointLights[i];
				pointLights[i] = nullptr;
			}
			
			if (spotLights[i] != nullptr)
			{
				delete spotLights[i];
				spotLights[i] = nullptr;
			}
		}
	}

	void LightManager::AddLight(LIGHT_TYPE type)
	{
		switch (type)
		{
		case LIGHT_TYPE::DIRECTIONAL:
			directionalLight = new DirectionalLight(render);
			break;
		case LIGHT_TYPE::POINTLIGHT:
			if (pointLightsCreated < lightMax)
			{
				pointLights[pointLightsCreated] = new PointLight(render);
				pointLightsCreated++;
			}
			break;
		case LIGHT_TYPE::SPOTLIGHT:
			if (spotLightsCreated < lightMax)
			{
				spotLights[spotLightsCreated] = new SpotLight(render);
				spotLightsCreated++;
			}
			break;
		default:
			break;
		}
	}

	void LightManager::UseLights(uint shaderId)
	{
		if (directionalLight != nullptr)
		{
			directionalLight->UseLight(shaderId);
		}

		for (int i = 0; i < lightMax; i++)
		{
			if (pointLights[i] != nullptr)
			{
				pointLights[i]->UseLight(shaderId, i);
			}
			if (spotLights[i] != nullptr)
			{
				spotLights[i]->UseLight(shaderId, i);
			}
		}
	}

	DirectionalLight* LightManager::GetDirectionalLight()
	{
		return directionalLight;
	}

	PointLight* LightManager::GetPointLight(int index)
	{
		if (index < 0 || index > lightMax - 1)
		{
			return nullptr;
		}

		return pointLights[index];
	}

	SpotLight* LightManager::GetSpotLight(int index)
	{
		if (index < 0 || index > lightMax - 1)
		{
			return nullptr;
		}

		return spotLights[index];
	}

	PointLight* LightManager::GetLasPointLightCreated()
	{
		return GetPointLight(pointLightsCreated - 1);
	}

	SpotLight* LightManager::GetLasSpotLightCreated()
	{
		return GetSpotLight(spotLightsCreated - 1);
	}
}