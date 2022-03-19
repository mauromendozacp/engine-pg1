#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "Input/input.h"
#include "Timer/timer.h"
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

		void Init(Input* input, Timer* timer, float fov, float width, float height, float near, float far);
		void Update();

		void SetData(glm::vec3 pos, float speed, float sensitivity);

		glm::mat4 GetView();
		glm::mat4 GetProjection();

	private:
		Input* input;
		Timer* timer;

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 pos;
		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;

		float speed;
		float sensitivity;

		void InputMove();
		void Rotate();
		void UpdateView();
	};
}

#endif // !CAMERA_H