#include "Renderer/renderer.h"

namespace GL
{
	Render::Render()
	{
		this->shader = new Shader();
		this->view = glm::mat4();
		this->projection = glm::mat4();
	}

	Render::~Render()
	{
		if (shader != NULL)
		{
			delete shader;
			shader = NULL;
		}
	}

	void Render::InitShader()
	{
		shader->CreateShader();
	}

	void Render::DeInitShader()
	{
		shader->DeleteShader();
	}

	void Render::BindBuffer(unsigned int VAO, unsigned int VBO, int tam, float* vertices)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::BindIndexs(unsigned int EBO, int tam, float* indexs)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
	}

	void Render::BindAttrib(unsigned int location, int size, int stride, int offset)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(location);
	}

	void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::Draw(unsigned int VAO, unsigned int VBO, unsigned int EBO, int tam, float* vertices)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glUseProgram(0);
	}

	void Render::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Render::ClearScreen()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render::PostRender(Window* window)
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}