#include "Renderer/renderer.h"


namespace GL
{
	Render::Render()
	{
		
	}
	Render::~Render()
	{

	}
	bool Render::Start(Window* win)
	{
		return false;
	}
	bool Render::Stop()
	{
		return false;
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
	void Render::SwapBuffers()
	{
		glfwSwapBuffers(window->GetWindow());
	}
}