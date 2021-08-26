#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include "../lib/GLFW/include/GLFW/glfw3.h"

namespace GL
{
	class GRAPHICSENGINE_API Render
	{
	private:
		unsigned int vertexArrayID;
		Window* window;
		std::string title;

		//mat4 model;
		//mat4 view;
		//mat4 projection;
		//mat4 mvp
		
		//void UpdateMVP();

	public:
		Render(Window* window);
		~Render();

		unsigned int GenerateBuffer(float* buffer, int size);
		void DestroyBuffer(unsigned int buffer);

		void LoadIdentityMat();
		void SetModelMat(/*mat4 mat*/);
		void MultiplyModelMat(/*mat4 mat*/);

		//mat4& GetMVP()

		void RenderTriangule();
		
		void BeginDrawing(unsigned int attribID);
		void BindBuffer(unsigned int vertexBuffer, unsigned int attribID);
		void DrawBuffer(int size);
		void EndDrawing(unsigned int attribID);

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender();
	};
}

#endif