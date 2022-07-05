#ifndef RENDER_H
#define RENDER_H

#include "exports.h"

#include "Window/window.h"
#include "Shader/shader.h"

#include "GLM/glm.hpp"
#include "GLM/ext/matrix_transform.hpp"
#include "GLM/gtc/type_ptr.hpp"
#include "GLEW/glew.h"

namespace GL
{
	class GRAPHICSENGINE_API Render
	{
	public:
		Render();
		~Render();

		void Init();
		void SetDepth();

		void UseShader();
		uint GetShaderId();
		void CleanShader();

		void GenBuffers(uint& VAO, uint& VBO, uint& EBO);
		void GenBuffers(uint& VAO, uint& VBO, uint& EBO, uint& UVB);
		void BindBuffer(uint VAO, uint VBO, int tam, const void* vertices);
		void BindBufferDynamic(uint VAO, uint VBO, int tam, const void* vertices);
		void BindIndexs(uint EBO, int tam, uint* indexs);
		void BindUV(uint UVB, int tam, float* vertices);
		void ReBindBuffer(uint VBO, int tam, const void* vertices);
		void UnBind(uint& VAO, uint& VBO, uint& EBO);
		void UnBind(uint& VAO, uint& VBO, uint& EBO, uint& UVB);

		void SetLocation(uint& location, const char* loc);
		void SetUniform(uint& uniform, const char* loc);
		void SetBaseAttribs(uint location, int size, GLsizei stride, const void* offset);
		void SetTextureAttribs(uint location, int size, int stride, int offset);

		void UpdateMVP(uint uniformModel, uint uniformView, uint uniformProjection, glm::mat4 model);
		void UpdateVec3Value(uint uniformVec3, glm::vec3 vec3Value);
		void UpdateColor(uint uniformBaseColor, uint uniformAlpha, glm::vec4 baseColor);
		void UpdateStatus(uint uniformStatus, bool status);
		void UpdateTexture(uint uniformTexture, uint textureId);
		void UpdateFloatValue(uint uniformFloat, float value);
		void UpdateIntValue(uint uniformInt, int value);
		uint GetUniform(uint shaderId, const char* loc);

		void SetView(glm::mat4 view);
		void SetProjection(glm::mat4 projection);

		void Draw(uint VAO, uint vertices);
		void DrawLines(uint VAO, uint vertices);

		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);

		void UseTexture(int number, uint id);
		void CleanTexture();
		void TextureEnable();
		void TextureDisable();
		void TextureDelete(uint uniformTexture, uint& textureId);
		void BlendEnable();
		void BlendDisable();

	private:
		Shader* shader;

		glm::mat4 view;
		glm::mat4 projection;
	};
}

#endif