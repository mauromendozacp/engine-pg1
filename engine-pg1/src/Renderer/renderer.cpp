#include "Renderer/renderer.h"

#include "../GLEW/glew.h"

namespace GL
{
	Render::Render()
	{
		this->shader = new Shader();

		view = glm::mat4(1.0f);
		view = glm::lookAt(glm::vec3(0, 0, -15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(90.0f), 640.0f / 480.0f, 0.1f, 1000.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
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

	void Render::BindBuffer(unsigned int& VAO, unsigned int& VBO, int tam, float* vertices)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::BindIndexs(unsigned int& EBO, int tam, unsigned int* indexs)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
	}

	void Render::BindAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::Draw(glm::mat4 model, glm::vec4 color, unsigned int VAO, unsigned int vertex)
	{
		glUseProgram(shader->GetShader());

		unsigned int modelLoc = glGetUniformLocation(shader->GetShader(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(shader->GetShader(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projectionLoc = glGetUniformLocation(shader->GetShader(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shader->GetShader(), "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shader->GetShader(), "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertex, GL_UNSIGNED_INT, 0);

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render::PostRender(Window* window)
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}