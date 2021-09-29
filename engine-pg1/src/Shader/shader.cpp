#include "shader.h"

namespace GL
{
	Shader::Shader()
	{
		shaderId = 0;
	}

	Shader::~Shader()
	{
	}

	void Shader::CreateShader()
	{
		shaderId = glCreateProgram();
		if (!shaderId) {
			std::cout << "Error creating the shader program!" << std::endl;
			return;
		}

		VertexShader();
		FragmentShader();
		LinkShader();
	}

	void Shader::VertexShader()
	{
		int success;
		char infoLog[512];
		std::string vertexShaderString = ReadShaderFile(vertexPath);
		const char* vertexShaderSource = vertexShaderString.c_str();

		uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		glAttachShader(shaderId, vertexShader);
	}

	void Shader::FragmentShader()
	{
		int success;
		char infoLog[512];
		std::string fragmentShaderString = ReadShaderFile(fragmentPath);
		const char* fragmentShaderSource = fragmentShaderString.c_str();

		uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		};
		glAttachShader(shaderId, fragmentShader);
	}

	void Shader::LinkShader()
	{
		int success;
		char infoLog[512];		

		glLinkProgram(shaderId);

		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
			std::cout << "Error validating program: " << infoLog << std::endl;
			return;
		}

		glUseProgram(shaderId);
	}

	void Shader::DeleteShader()
	{
		if (shaderId != 0)
		{
			glDeleteProgram(shaderId);
			shaderId = 0;
		}
	}

	std::string Shader::ReadShaderFile(std::string path)
	{
		std::string shaderCode;
		std::ifstream vShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(path);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			vShaderFile.close();
			shaderCode = vShaderStream.str();
		}
		catch (std::ifstream::failure& e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		return shaderCode;
	}
}