#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include <fstream>
#include <sstream>

namespace GL
{
	const std::string vertexPath =  "../src/Shaders/vertexshader.txt";
	const std::string fragmentPath = "../src/Shaders/fragmentshader.txt";

	class GRAPHICSENGINE_API Render
	{
	private:
		Window* window;
		unsigned int vertexArrayID;
		std::string title;

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

		void BindBuffer(unsigned int VAO, unsigned int VBO, unsigned int EBO, float* vertices);
		void RenderBuffer();
		void UseShader();

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender();
	};
}

#endif