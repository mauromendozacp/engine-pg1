#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include "Shader/shader.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Render
	{
	public:
		Render();
		~Render();

		void Init();
		void SetDepth();

		void UseShader(uint shaderId);
		uint GetSolidShaderId();
		uint GetTextureShaderId();
		void CleanShader();

		void GenBuffers(uint& VAO, uint& VBO, uint& EBO);
		void GenBuffers(uint& VAO, uint& VBO, uint& EBO, uint& UVB);
		void BindBuffer(uint VAO, uint VBO, int tam, float* vertices);
		void BindIndexs(uint EBO, int tam, uint* indexs);
		void BindUV(uint UVB, int tam, float* vertices);
		void UnBind(uint& VAO, uint& VBO, uint& EBO);
		void UnBind(uint& VAO, uint& VBO, uint& EBO, uint& UVB);

		void SetLocation(uint shaderId, uint& location, const char* loc);
		void SetUniform(uint shaderId, uint& uniform, const char* loc);
		void SetBaseAttribs(uint location, int size, int stride, int offset);
		void SetTextureAttribs(uint location, int size, int stride, int offset);

		void UpdateMVP(uint uniformModel, uint uniformView, uint uniformProjection, glm::mat4 model);
		void UpdateVec3(uint uniformVec3, glm::vec3 vec3Value);
		void UpdateColor(uint uniformBaseColor, uint uniformAlpha, glm::vec4 baseColor);
		void UpdateStatus(uint uniformStatus, bool status);
		void UpdateLight(uint uniformLight, glm::vec3 light);
		void UpdateTexture(uint uniformTexture, uint textureId);
		void UpdateFloatValue(uint uniformFloat, float value);
		void UpdateIntValue(uint uniformInt, int value);
		void UpdateCameraView(uint shaderId, glm::vec3 position, const char* loc);
		void UpdateLightVec3(uint shaderId, glm::vec3 light, const char* loc);
		void UpdateLightFloat(uint shaderId, float value, const char* loc);
		void UpdateLightStatus(uint shaderId, bool status, const char* loc);
		uint GetUniform(uint shaderId, const char* loc);

		void SetView(glm::mat4 view);
		void SetProjection(glm::mat4 projection);

		void Draw(uint VAO, uint VBO, uint& EBO, uint vertices, uint tamVerts, float* vertexs);
		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);
		void BindDiffuseMap(uint textureId);
		void BindSpecularMap(uint textureId);
		void TextureDisable();
		void TextureDelete(uint uniformTexture, uint& textureId);
		void BlendEnable();
		void BlendDisable();

	private:
		Shader* solidShader;
		Shader* textureShader;

		glm::mat4 view;
		glm::mat4 projection;
	};
}

#endif