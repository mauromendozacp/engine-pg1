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

	void Render::GenerateBuffer(float* buffer, int size)
	{
		
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
	void Render::RenderBufferTriangule()
	{
		/*glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();*/

		float positions[6] = {
			-0.5f, -0.5f,
			 0.0f,  -0.5f,
			 0.5f, -0.5f
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Render::Draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
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