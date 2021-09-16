#include "Renderer/renderer.h"

namespace GL
{
	Render::Render(Window* window)
	{
		this->window = window;
		this->vertexArrayID = NULL;
		this->title = "";

		this->shaderProgram = NULL;
		this->vertexShader = NULL;
		this->fragmentShader = NULL;

		this->VBO = NULL;
		this->VAO = NULL;
		this->EBO = NULL;
	}

	Render::~Render()
	{
		if (window != nullptr)
		{
			delete window;
			window = nullptr;
		}
	}

	void Render::CreateShader()
	{
		VertexShader();
		FragmentShader();
		LinkShader();
	}

	void Render::VertexShader()
	{
		const char* vertexShaderSource = ReadShaderFile(vertexPath);

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
	}

	void Render::FragmentShader()
	{
		const char* fragmentShaderSource = ReadShaderFile(fragmentPath);

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
	}

	void Render::LinkShader()
	{
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glUseProgram(shaderProgram);
	}

	void Render::DeleteShader()
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	const char* Render::ReadShaderFile(std::string path)
	{
		std::string shaderCode;
		std::ifstream vShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			vShaderFile.close();
			shaderCode = vShaderStream.str();
		}
		catch (std::ifstream::failure & e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		return shaderCode.c_str();
	}

	void Render::RenderBufferTriangule()
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Render::Draw()
	{
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(shaderProgram);
	}

	void Render::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Render::ClearScreen()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render::PostRender()
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}