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
		//Compila, adjunta y linkea los shaders al programa para ser usados más adelante

		uint GetShaderId();
		
	private:
		uint shaderId;

		void VertexShader(std::string vertexPath);//Compila y adjunta el vertex shader al programa
		void FragmentShader(std::string fragmentPath);//Compila y adjunta el fragment shader al programa
		void LinkShader();//Linkea todos los shaders agregados al programa y crea un exe de los mismos para utilizar donde corresponda
		std::string ReadShaderFile(std::string path);//Devuelve la información de un archivo de shader
	};
}

#endif // !SHADER_H
