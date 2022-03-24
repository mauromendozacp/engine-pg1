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

	void Render::Init()
	{
		solidShader->CreateShader("../src/ShadersCode/SolidVertex.shader", "../src/ShadersCode/SolidFragment.shader");
		textureShader->CreateShader("../src/ShadersCode/TextureVertex.shader", "../src/ShadersCode/TextureFragment.shader");
	}

	void Render::UseShaderId(uint shaderId)
	{
		glUseProgram(shaderId);
	}

	uint Render::GetSolidShaderId()
	{
		return solidShader->GetShader();
	}

	uint Render::GetTextureShaderId()
	{
		return textureShader->GetShader();
	}

	void Render::CleanShaderId()
	{
		glUseProgram(0);
	}

	void Render::SetBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Render::SetDepth()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void Render::BindBuffer(uint& VAO, uint& VBO, int tam, float* vertices)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::BindIndexs(uint& EBO, int tam, uint* indexs)
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

	void Render::UnBind(uint& VAO, uint& VBO, uint& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::SetUniform(uint shaderId, uint& uniform, const char* loc)
	{
		uniform = glGetUniformLocation(shaderId, loc);
	}

	void Render::UpdateMVP(glm::mat4 model, uint uniformModel, uint uniformView, uint uniformProjection)
	{
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void Render::UpdateColor(glm::vec4 color, uint uniformColor, uint uniformAlpha)
	{
		glUniform3fv(uniformColor, 1, glm::value_ptr(glm::vec3(color.r, color.g, color.b)));
		glUniform1fv(uniformAlpha, 1, &(color.a));
	}

	void Render::UpdateTexture(uint textureId, uint uniformTexture)
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1f(uniformTexture, (GLfloat)textureId);
	}

	void Render::SetView(glm::mat4 view)
	{
		this->view = view;
	}

	void Render::SetProjection(glm::mat4 projection)
	{
		this->projection = projection;
	}

	void Render::BindTextureBuffer(uint& VBO, int tam, float* vertices)
	{
		glGenBuffers(tam, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::Draw(uint VAO, uint VBO, uint& EBO, uint vertices, uint tamVerts, float *vertexs)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ARRAY_BUFFER, tamVerts, vertexs, GL_STATIC_DRAW);

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
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Render::PostRender(Window* window)
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}