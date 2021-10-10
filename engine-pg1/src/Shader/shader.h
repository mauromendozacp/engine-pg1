#ifndef SHADER_H
#define SHADER_H

#include "exports.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace GL
{
	typedef unsigned int uint;

	class GRAPHICSENGINE_API Shader
	{
	public:
		Shader();
		~Shader();

		void CreateShader(std::string vertexPath, std::string fragmentPath);
		uint GetShader();
		
	private:
		uint shaderId;

		void VertexShader(std::string vertexPath);
		void FragmentShader(std::string fragmentPath);
		void LinkShader();
		std::string ReadShaderFile(std::string path);
	};
}

#endif // !SHADER_H
