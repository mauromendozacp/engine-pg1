#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include <fstream>
#include <sstream>
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"

namespace GL
{
	const std::string vertexPath =  "../src/Shaders/vertexshader.txt";
	const std::string fragmentPath = "../src/Shaders/fragmentshader.txt";

	class GRAPHICSENGINE_API Render
	{
	private:
		Window* window;
		glm::mat4 view;
		glm::mat4 projection;
		unsigned int vertexArrayID;

		unsigned int shaderProgram;
		unsigned int vertexShader;
		unsigned int fragmentShader;

	public:
		Render(Window* window);
		~Render();

		void CreateShader();
		void VertexShader();
		void FragmentShader();
		void LinkShader();
		void DeleteShader();
		std::string ReadShaderFile(std::string path);

		void BindBuffer(unsigned int VAO, unsigned int VBO, int tam, float* vertices);
		void BindIndexs(unsigned int EBO, int tam, float* indexs);
		void BindAttrib(unsigned int location, int size, int stride, int offset);
		void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);
		void Draw(unsigned int VAO, unsigned int VBO, unsigned int EBO, int tam, float* vertices);

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender();
	};
}

#endif