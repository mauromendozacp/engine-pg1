#include "Renderer/renderer.h"

#include "../GLEW/glew.h"

namespace GL
{
	Render::Render()
	{
		this->solidShader = new Shader();
		this->textureShader = new Shader();

		view = glm::mat4(1.0f);
		view = glm::lookAt(glm::vec3(0, 0, -15), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
		projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(90.0f), 640.0f / 480.0f, 0.1f, 1000.0f);
		
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		
		/*glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	}

	Render::~Render()
	{
		if (solidShader != NULL)
		{
			delete solidShader;
			solidShader = NULL;
		}
		if (textureShader != NULL)
		{
			delete textureShader;
			textureShader = NULL;
		}
	}

	void Render::InitShader()
	{
		solidShader->CreateShader("../src/ShadersCode/SolidVertex.shader", "../src/ShadersCode/SolidFragment.shader");
		textureShader->CreateShader("../src/ShadersCode/TextureVertex.shader", "../src/ShadersCode/TextureFragment.shader");
	}

	void Render::UseShaderId(unsigned int shaderId)
	{
		glUseProgram(shaderId);
	}

	unsigned int Render::GetSolidShaderId()
	{
		return solidShader->GetShader();
	}

	unsigned int Render::GetTextureShaderId()
	{
		return textureShader->GetShader();
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

	void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::Draw(glm::mat4 model, unsigned int VAO, unsigned int vertex, unsigned int shaderId)
	{
		unsigned int modelLoc = glGetUniformLocation(shaderId, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, vertex, GL_UNSIGNED_INT, 0);
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