#ifndef RENDER_H
#define RENDER_H

#include "Window/window.h"
#include "Camera/camera.h"
#include "Shader/shader.h"
#include "glm.hpp"
#include "../glm/ext/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

namespace GL
{
	class GRAPHICSENGINE_API Render
	{
	private:
		Shader* solidShader;
		Shader* textureShader;

		Camera* camera;

	public:
		Render(Camera* camera);
		~Render();

		void Init(bool alpha);
		void UseShaderId(unsigned int shaderId);
		unsigned int GetSolidShaderId();
		unsigned int GetTextureShaderId();

		void BindBuffer(unsigned int& VAO, unsigned int& VBO, int tam, float* vertices);
		void BindIndexs(unsigned int& EBO, int tam, unsigned int* indexs);
		void BindBaseAttrib();
		void BindExtraAttrib();
		void UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO);

		void SetShader(unsigned int shaderId, glm::vec4 color);
		void SetShader(unsigned int shaderId, glm::vec4 color, unsigned int textureId);
		
		void BindTextureBuffer(unsigned int& VBO, int tam, float* vertices);

		void Draw(glm::mat4 model, unsigned int VAO, unsigned int VBO, unsigned int& EBO, unsigned int vertices, unsigned int tamVerts, float* vertexs, unsigned int shaderId);
		void SetClearColor(float r, float g, float b, float a);
		void ClearScreen();
		void PostRender(Window* window);
	};
}

#endif