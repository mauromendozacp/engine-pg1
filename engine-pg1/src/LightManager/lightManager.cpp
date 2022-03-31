#include "lightManager.h"

namespace GL
{
	LightManager::LightManager()
	{
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

	void LightManager::Init(Render* render)
	{
		directionalLight = new DirectionalLight(render);
		directionalLight->Init();

		for (int i = 0; i < lightMax; i++)
		{
			pointLights[i] = new PointLight(render);
			pointLights[i]->Init();

			spotLights[i] = new SpotLight(render);
			spotLights[i]->Init();
		}
	}

	void LightManager::UseLights()
	{
		if (directionalLight->IsEnabled())
		{
			directionalLight->UseLight();
		}

		for (int i = 0; i < lightMax; i++)
		{
			if (pointLights[i]->IsEnabled())
			{
				pointLights[i]->UseLight();
			}
			if (spotLights[i]->IsEnabled())
			{
				spotLights[i]->UseLight();
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
}