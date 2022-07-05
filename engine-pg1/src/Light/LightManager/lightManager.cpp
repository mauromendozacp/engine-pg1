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
			directionalLight->SetUniforms();
			break;
		case LIGHT_TYPE::POINTLIGHT:
			if (pointLightsCreated < lightMax)
			{
				pointLights[pointLightsCreated] = new PointLight(render);
				pointLights[pointLightsCreated]->SetUniforms(pointLightsCreated);
				pointLightsCreated++;
			}
			break;
		case LIGHT_TYPE::SPOTLIGHT:
			if (spotLightsCreated < lightMax)
			{
				spotLights[spotLightsCreated] = new SpotLight(render);
				spotLights[spotLightsCreated]->SetUniforms(spotLightsCreated);
				spotLightsCreated++;
			}
			break;
		default:
			break;
		}
	}

	void LightManager::Update()
	{
		render->UseShader();

		if (directionalLight != nullptr)
		{
			directionalLight->UpdateShader();
		}

		for (int i = 0; i < lightMax; i++)
		{
			if (pointLights[i] != nullptr)
			{
				pointLights[i]->UpdateShader();
			}
			if (spotLights[i] != nullptr)
			{
				spotLights[i]->UpdateShader();
			}
		}

		render->CleanShader();
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