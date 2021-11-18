#include "window.h"

namespace GL
{
	Window::Window(float width, float height, std::string title)
	{//Crea la ventana partiendo del ancho, alto y titulo ingresados. La ventana de glfw todavia no se inicia.
		this->glfWindow = nullptr;
		this->height = height;
		this->width = width;
		this->title = title;
	}

	Window::~Window()
	{
	}

	GLFWwindow* Window::GetWindow()
	{
		return glfWindow;
	}

	bool Window::OpenWindow()
	{//En este paso es que se inicia la ventana de glfw. Devuelve un bool en caso de ser posible (o no) crear la ventana. 
		glfWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr); 
		//Usando los campos internos ademas de otros 2, se intentara recrear la ventana.
		//El primer nullptr referencia a un monitor* que servira para pantalla completa.
		//El segundo nullptr referencia a otra ventana para utilizarla y/o compartir recursos con ella.
		if (!glfWindow) //En caso de no poder abrirse.
		{
			glfwTerminate(); //El glfw se cierra evitando problemas futuros.
			return false;
		}
		return true;
	}

	void Window::CloseWindow()
	{
		glfwTerminate();
	}

	void Window::DestroyWindow()
	{
		glfwDestroyWindow(glfWindow);
	}
}