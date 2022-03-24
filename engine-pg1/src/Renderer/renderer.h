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
	private:
		Shader* shader;

		glm::mat4 view;
		glm::mat4 projection;

	public:
		Render();
		~Render();

		void Init();
		void SetBlend();
		void SetDepth();

		void UseShader();
		uint GetShaderId();
		void CleanShader();

		void BindBuffer(uint& VAO, uint& VBO, int tam, float* vertices);
		void BindIndexs(uint& EBO, int tam, uint* indexs);
		void BindTextureBuffer(uint& VBO, int tam, float* vertices);
		void BindBaseAttrib();
		void BindExtraAttrib();
		void UnBind(uint& VAO, uint& VBO, uint& EBO);

		void SetUniform(uint& uniform, const char* loc);
		void SetAttribs(uint uniform, int size, int stride, int offset);

		void UpdateMVP(glm::mat4 model, uint uniformModel, uint uniformView, uint uniformProjection);
		void UpdateViewPosition(glm::vec3 viewPosition, uint uniformViewPosition);
		void UpdateColor(glm::vec4 baseColor, uint uniformBaseColor, uint uniformAlpha);
		void UpdateStatus(bool status, uint uniformStatus);
		void UpdateLight(glm::vec3 lightColor, uint uniformLightColor);
		void UpdateTexture(uint textureId, uint uniformTexture);
		void UpdateUseTexture(bool useTexture, uint uniformUseTexture);

		void SetView(glm::mat4 view);
		void SetProjection(glm::mat4 projection);

		void Draw(uint VAO, uint VBO, uint& EBO, uint vertices, uint tamVerts, float* vertexs);
		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);
	};
}

#endif