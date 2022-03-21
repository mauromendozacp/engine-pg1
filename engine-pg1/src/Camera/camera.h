#ifndef CAMERA_H
#define CAMERA_H

#include "exports.h"
#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	class GRAPHICSENGINE_API Camera
	{
	public:
		Camera(Render* render, Input* input);
		~Camera();

		void Init(float fov, float width, float height, float near, float far);
		void Update(float deltaTime);

		void SetData(glm::vec3 pos, float speed, float sensitivity);
		void SetPosition(glm::vec3 pos);
		glm::vec3 GetPosition();
		glm::vec3 GetFront();
		glm::vec3 GetUp();

		glm::mat4 GetView();
		glm::mat4 GetProjection();

	private:
		Render* render;
		Input* input;

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 pos;
		glm::vec3 front;
		glm::vec3 up;

		float yaw;
		float pitch;

		float speed;
		float sensitivity;

		void InputMove(float deltaTime);
		void Rotate();
		void UpdateView();
	};
}

#endif // !CAMERA_H