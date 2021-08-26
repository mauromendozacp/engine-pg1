#include "Renderer/renderer.h"

namespace GL
{
	Render::Render(Window* window)
	{
		this->window = window;
		this->vertexArrayID = NULL;
		this->title = "";
	}

	Render::~Render()
	{
		if (window != nullptr)
		{
			delete window;
			window = nullptr;
		}
	}

	unsigned int Render::GenerateBuffer(float* buffer, int size)
	{
		return 0;
	}
	void Render::DestroyBuffer(unsigned int buffer)
	{
		
	}
	void Render::LoadIdentityMat()
	{

	}
	void Render::SetModelMat()
	{

	}
	void Render::MultiplyModelMat()
	{

	}
	void Render::RenderTriangule()
	{
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}
	void Render::BeginDrawing(unsigned int attribID)
	{
		glBegin(GLenum());
	}
	void Render::BindBuffer(unsigned int vertexBuffer, unsigned int attribID)
	{
		
	}
	void Render::DrawBuffer(int size)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, 0, size);
	}
	void Render::EndDrawing(unsigned int attribID)
	{

	}
	
	void Render::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void Render::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Render::PostRender()
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}