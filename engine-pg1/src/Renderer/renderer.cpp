#include "Renderer/renderer.h"
#include "../GLEW/glew.h"

namespace GL
{
	Render::Render()
	{
		this->shader = nullptr;

		view = glm::mat4(0.f);
		projection = glm::mat4(0.f);
	}

	Render::~Render()
	{
		if (shader != nullptr)
		{
			delete shader;
			shader = nullptr;
		}
	}

	void Render::Init()
	{
		shader = new Shader();
		shader->CreateShader("../src/ShadersCode/vertex.shader", "../src/ShadersCode/fragment.shader");
	}

	void Render::UseShader()
	{
		glUseProgram(GetShaderId());
	}

	uint Render::GetShaderId()
	{
		return shader->GetShaderId();
	}

	void Render::CleanShader()
	{
		glUseProgram(0);
	}

	void Render::SetDepth()
	{
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void Render::GenBuffers(uint& VAO, uint& VBO, uint& EBO)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
	}

	void Render::GenBuffers(uint& VAO, uint& VBO, uint& EBO, uint& UVB)
	{
		GenBuffers(VAO, VBO, EBO);
		glGenBuffers(1, &UVB);
	}

	void Render::BindBuffer(uint VAO, uint VBO, int tam, float* vertices)
	{
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
	}

	void Render::BindIndexs(uint EBO, int tam, uint* indexs)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
	}

	void Render::BindUV(uint UVB, int tam, float* vertices)
	{
		glBindBuffer(GL_ARRAY_BUFFER, UVB);
		glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_DYNAMIC_DRAW);
	}

	void Render::UnBind(uint& VAO, uint& VBO, uint& EBO)
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	void Render::UnBind(uint& VAO, uint& VBO, uint& EBO, uint& UVB)
	{
		UnBind(VAO, VBO, EBO);
		glDeleteBuffers(1, &UVB);
	}

	void Render::SetLocation(uint& location, const char* loc)
	{
		location = glGetAttribLocation(GetShaderId(), loc);
	}

	void Render::SetUniform(uint& uniform, const char* loc)
	{
		uniform = glGetUniformLocation(GetShaderId(), loc);
	}

	void Render::SetBaseAttribs(uint location, int size, int stride, int offset)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
		glEnableVertexAttribArray(location);
	}

	void Render::SetTextureAttribs(uint location, int size, int stride, int offset)
	{
		glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
		glEnableVertexAttribArray(location);
	}

	void Render::UpdateMVP(uint uniformModel, uint uniformView, uint uniformProjection, glm::mat4 model)
	{
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	}

	void Render::UpdateVec3(uint uniformVec3, glm::vec3 vec3Value)
	{
		glUniform3f(uniformVec3, vec3Value.x, vec3Value.y, vec3Value.z);
	}

	void Render::UpdateColor(uint uniformBaseColor, uint uniformAlpha, glm::vec4 baseColor)
	{
		glUniform3fv(uniformBaseColor, 1, glm::value_ptr(glm::vec3(baseColor.r, baseColor.g, baseColor.b)));
		glUniform1fv(uniformAlpha, 1, &(baseColor.a));
	}

	void Render::UpdateStatus(uint uniformStatus, bool status)
	{
		glUniform1i(uniformStatus, status);
	}

	void Render::UpdateLight(uint uniformLight, glm::vec3 light)
	{
		glUniform3fv(uniformLight, 1, glm::value_ptr(light));
	}

	void Render::UpdateTexture(uint uniformTexture, uint textureId)
	{
		glUniform1f(uniformTexture, (GLfloat)textureId);
	}

	void Render::UpdateFloatValue(uint uniform, float value)
	{
		glUniform1f(uniform, value);
	}

	void Render::SetView(glm::mat4 view)
	{
		this->view = view;
	}

	void Render::SetProjection(glm::mat4 projection)
	{
		this->projection = projection;
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

	void Render::TextureEnable(uint textureId)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void Render::TextureDisable()
	{
		glDisable(GL_TEXTURE_2D);
	}

	void Render::TextureDelete(uint uniformTexture, uint& textureId)
	{
		glDeleteTextures(uniformTexture, &textureId);
	}

	void Render::BlendEnable()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Render::BlendDisable()
	{
		glDisable(GL_BLEND);
	}
}