#ifndef EXPORTS_H
#define EXPORTS_H

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#ifdef GRAPHICSENGINE_EXPORTS
	#define GRAPHICSENGINE_API __declspec(dllexport)
#else
	#define GRAPHICSENGINE_API __declspec(dllexport) //Revisar
#endif // GRAPHICSENGINE_EXPORTS

#endif // !EXPORTS_H

//Este documento hace que se puedan sacar las funciones de la libreria y poder usarlas en otro lado
//Esto se da cuando aparezca GRAPHICSENGINE_API en algun lado
//__declspec(dllexport) funciona para sacar las funciones de la lib
//__declspec(dllimport) funciona para ingresar funciones externas a la lib