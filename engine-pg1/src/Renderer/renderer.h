#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include "Shader/shader.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

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

		void BindBuffer(unsigned int& VAO, unsigned int& VBO, int tam, float* vertices);
		void BindIndexs(unsigned int& EBO, int tam, unsigned int* indexs);
		void BindAttrib();
		void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void Draw(glm::mat4 model, glm::vec4 color, unsigned int VAO, float* indexes);
		void Draw(glm::mat4 model, glm::vec4 color, unsigned int VAO, unsigned int vertices);

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);
	};
}

#endif