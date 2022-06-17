#ifndef SOLID_MATERIAL_H
#define SOLID_MATERIAL_H

#include "Material/material.h"

namespace GL
{
	class GRAPHICSENGINE_API SolidMaterial : public Material
	{
	public:
		SolidMaterial(Render* render);
		~SolidMaterial();

		void Init() override;
		void UpdateShader() override;

		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);

		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();

	private:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		uint uniformAmbient;
	};
}

#endif // !SOLID_MATERIAL_H
