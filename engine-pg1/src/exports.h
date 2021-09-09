#ifndef EXPORTS_H
#define EXPORTS_H

#include "../lib/GLEW/glew.h"
#include "../lib/GLFW/include/GLFW/glfw3.h"

#ifdef GRAPHICSENGINE_EXPORTS
	#define GRAPHICSENGINE_API __declspec(dllexport)
#else
	#define GRAPHICSENGINE_API __declspec(dllexport)
#endif // GRAPHICSENGINE_EXPORTS

#endif // !EXPORTS_H