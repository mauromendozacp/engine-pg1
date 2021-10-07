#ifndef SHADER_H
#define SHADER_H

#include "exports.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GL
{
	const std::string vertexPath = "../src/ShadersCode/vertexshader.shader";
	const std::string fragmentPath = "../src/ShadersCode/fragmentshader.shader";
	typedef unsigned int uint;

	class GRAPHICSENGINE_API Shader
	{
	public:
		Shader();
		~Shader();

		void CreateShader();
		void DeleteShader();
		uint GetShader();
		
	private:
		uint shaderId;

		void VertexShader();
		void FragmentShader();
		void LinkShader();
		std::string ReadShaderFile(std::string path);
	};
}

#endif // !SHADER_H
