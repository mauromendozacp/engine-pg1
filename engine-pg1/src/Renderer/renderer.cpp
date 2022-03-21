#include "Renderer/renderer.h"
#include "../GLEW/glew.h"

namespace GL
{
	Render::Render()
	{
		this->solidShader = new Shader();
		this->textureShader = new Shader();

		view = glm::mat4(0.f);
		projection = glm::mat4(0.f);
	}

	Render::~Render()
	{
		if (solidShader != nullptr)
		{
			delete solidShader;
			solidShader = nullptr;
		}
		if (textureShader != nullptr)
		{
			delete textureShader;
			textureShader = nullptr;
		}
	}

	void Render::Init(bool alpha)
	{
		if (alpha)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}

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

	void Render::BindBaseAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	void Render::BindExtraAttrib()
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::SetShader(unsigned int shaderId, glm::vec4 color)
	{
		glm::vec3 newColor = glm::vec3(color.r, color.g, color.b);
		unsigned int colorLoc = glGetUniformLocation(shaderId, "color");
		glUniform3fv(colorLoc, 1, glm::value_ptr(newColor));

		unsigned int alphaLoc = glGetUniformLocation(shaderId, "a");
		glUniform1fv(alphaLoc, 1, &(color.a));
	}

	void Render::SetShader(unsigned int shaderId, glm::vec4 color, unsigned int textureId)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);

		SetShader(shaderId, color);

		unsigned int textureLoc = glGetUniformLocation(shaderId, "ourTexture");
		glUniform1f(textureLoc, (GLfloat)textureId);
	}

	void Render::SetView(glm::mat4 view)
	{
		this->view = view;
	}

	void Render::SetProjection(glm::mat4 projection)
	{
		this->projection = projection;
	}

	void Render::BindTextureBuffer(unsigned int& VBO, int tam, float* vertices)
	{
		glGenBuffers(tam, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::Draw(glm::mat4 model, unsigned int VAO, unsigned int VBO, unsigned int& EBO, unsigned int vertices, unsigned int tamVerts, float *vertexs, unsigned int shaderId)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, tamVerts, vertexs, GL_STATIC_DRAW);

		unsigned int modelLoc = glGetUniformLocation(shaderId, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		unsigned int viewLoc = glGetUniformLocation(shaderId, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projectionLoc = glGetUniformLocation(shaderId, "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		if (vertices == 3)
			glDrawArrays(GL_TRIANGLES, 0, vertices);
		else
			glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);

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