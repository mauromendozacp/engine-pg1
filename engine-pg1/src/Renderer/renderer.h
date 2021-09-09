#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"

namespace GL
{
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

		void RenderBufferTriangule();
		void Draw();

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender();
	};
}

#endif