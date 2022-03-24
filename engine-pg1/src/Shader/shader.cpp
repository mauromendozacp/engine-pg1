#include "shader.h"

namespace GL
{
	Shader::Shader()
	{
		shaderId = 0;
	}

	Shader::~Shader()
	{
		glDeleteProgram(shaderId);
	}

	void Shader::CreateShader(std::string vertexPath, std::string fragmentPath)
	{
		shaderId = glCreateProgram();
		if (!shaderId) {
			std::cout << "Error creating the shader program!" << std::endl;
			return;
		}

		VertexShader(vertexPath);
		FragmentShader(fragmentPath);
		LinkShader();
	}

	void Shader::VertexShader(std::string vertexPath)
	{
		int success;
		char infoLog[512];
		std::string vertexShaderString = ReadShaderFile(vertexPath);
		//Se almacena el shader en si
		const char* vertexShaderSource = vertexShaderString.c_str();
		//Se almacena el shader, pero en un array de chars

		uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		//Se crea un shader (por el momento vacio) especificando que es Vertex
		
		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		//En orden 1, 2, 3, 4:
		// 1 - Se indica qué shader va a modificarse
		// 2 - Se indica la cantidad de elementos a modificar
		// 3 - Se indica el texto por el cuál se reemplazará la información del shader
		// 4 - Se especifica el largo del texto que se debe utilizar
		
		glCompileShader(vertexShader);
		//Literalmente compila el shader con la información brindada en el source
		
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		//Devuelve un parámetro del shader
		//En orden 1, 2, 3:
		// 1 - Se indica el shader del que se quiere comprobar el estado
		// 2 - Se indica qué es lo que se quiere buscar (en este caso, el estado de compilación)
		// 3 - Se pasa como referencia el puntero de la variable en la que quiero recibir el estado de compilación

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
			//Devuelve el log de información del shader
			//En orden 1, 2, 3, 4:
			// 1 - Se indica el shader del que se quiere recibir la info
			// 2 - Se indica el tamaño máximo de lo que se busca mostrar (en este caso, el log tiene 512)
			// 3 - Devuelve el tamaño real de lo que se recibe 
			// 4 - Se indica el string donde se guardará el log

			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		};

		glAttachShader(shaderId, vertexShader);
		//Agrega el shader al programa anteriormente creado.
	}

	void Shader::FragmentShader(std::string fragmentPath)
	{//Esto es exáctamente igual al Vertex Shader pero cambiando los paths y referencias a fragment
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
	{//Es el último eslabón de la cadena del shader. Gracias a esto, es que se puede ejecutar el shader mismo.
		int success;
		char infoLog[512];		

		glLinkProgram(shaderId);
		//Literalmente crea el programa con los shaders cargados.

		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		//Devuelve un parámetro del programa
		//En orden 1, 2, 3:
		// 1 - Se indica el programa del que se quiere comprobar un parámetro
		// 2 - Se indica qué es lo que se quiere buscar (en este caso, el estado de linkeo)
		// 3 - Se pasa como referencia el puntero de la variable en la que quiero recibir el estado de linkeo

		if (!success)
		{
			glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}

		glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &success);
		//Se busca que el programa esté en óptimas condiciones para poder funcionar

		if (!success) {
			glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
			std::cout << "Error validating program: " << infoLog << std::endl;
			return;
		}

		glUseProgram(shaderId);
		//Genera los ejecutables de los distintos shaders cargados en el programa.
		//Esto solamente es posible cuando se COMPILARON los shaders, se CARGARON en el programa y se LINKEO el programa.

	}

	uint Shader::GetShaderId()
	{
		return shaderId;
	}

	std::string Shader::ReadShaderFile(std::string path)
	{//Devuelve la información de un archivo de shader
		std::string shaderCode; //contiene la informacion del shader
		std::ifstream vShaderFile; //Esto es un input/output confirmado, en base a eso, hace cosas

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		//Failbit: recibir un dato erroneo.
		//Badbit: tener un error de logica.
		//exceptions se fija si hay alguno de esos errores y tira el error.
		try 
		{
			//Intentara abrir el archivo donde se encuentra el shader
			vShaderFile.open(path); 
			std::stringstream vShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			//rdbuf obtiene un puntero al filebuf
			//Se agrega la informacion del shaderFile al ShaderStream
			vShaderFile.close();
			shaderCode = vShaderStream.str();
			//Se parsea el contenido del stream a string
		}
		catch (std::ifstream::failure& e) 
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		return shaderCode;
	}
}