#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "Input/input.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace GL
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Init(glm::vec3 position, float fov, float width, float height, float near, float far);
		void Update();

		glm::mat4 GetView();
		glm::mat4 GetProjection();

	private:
		Input* input;

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 pos;
		glm::vec3 front;
		glm::vec3 up;		

		float speed;
		float sensitivity;

		void InputMove();
		void InputAxis();
	};
}

#endif // !CAMERA_H