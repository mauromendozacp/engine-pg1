#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include "Shader/shader.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Render
	{
	private:
		Shader* shader;
		glm::mat4 view;
		glm::mat4 projection;

	public:
		Render();
		~Render();

		void InitShader();
		void DeInitShader();

		void BindBuffer(unsigned int VAO, unsigned int VBO, int tam, float* vertices);
		void BindIndexs(unsigned int EBO, int tam, float* indexs);
		void BindAttrib(unsigned int location, int size, int stride, int offset);
		void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void Draw(unsigned int VAO, unsigned int VBO, unsigned int EBO, int tam, float* vertices);

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);
	};
}

#endif