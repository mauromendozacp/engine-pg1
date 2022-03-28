#ifndef LIGHT_H
#define LIGHT_H

#include "exports.h"
#include "Entity/entity.h"
#include "Color/color.h"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Light : public Entity
	{
	public:
		Light(Render* render);
		~Light();

		Color color;

		virtual void Init();
		virtual void UseLight();

		void SetDirection(glm::vec3 direction);
		void SetAmbient(glm::vec3 ambient);
		void SetDiffuse(glm::vec3 diffuse);
		void SetSpecular(glm::vec3 specular);
		void SetEnabled(bool enabled);

		glm::vec3 GetColor();
		glm::vec3 GetDirection();
		glm::vec3 GetAmbient();
		glm::vec3 GetDiffuse();
		glm::vec3 GetSpecular();
		bool IsEnabled();

	protected:
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		bool enabled;

		uint uniformColor;
		uint uniformPosition;
		uint uniformDirection;
		uint uniformAmbient;
		uint uniformDiffuse;
		uint uniformSpecular;
		uint uniformEnabled;
	};
}

#endif // !LIGHT_H