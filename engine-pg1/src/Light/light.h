#ifndef LIGHT_H
#define LIGHT_H

#include "exports.h"
#include "Entity/entity.h"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Light : public Entity
	{
	public:
		Light(Render* render);
		~Light();

		void SetColor(glm::vec3 color);
		glm::vec3 GetColor();

	protected:
		glm::vec3 color;
		glm::vec3 direction;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}

#endif // !LIGHT_H