#include "Renderer/renderer.h"

namespace GL
{
	Render::Render(Window* window)
	{
		this->window = window;
		this->vertexArrayID = NULL;
		this->title = "";
		this->shaderProgram = 0;
		this->vertexShader = 0;
		this->fragmentShader = 0;
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
		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
			"}\0";

		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);
	}

	void Render::FragmentShader()
	{
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\0";

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

	void Render::RenderBufferTriangule()
	{
		float positions[6] = {
			-0.5f, -0.5f,
			 0.0f,  -0.5f,
			 0.5f, -0.5f
		};

		unsigned int buffer;
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glUseProgram(shaderProgram);
	}

	void Render::Draw()
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void Render::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Render::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render::PostRender()
	{
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	}
}