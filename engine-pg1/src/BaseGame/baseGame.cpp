#include "baseGame.h"

#include "Renderer/renderer.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
		render = new Render(window);
	}

	BaseGame::~BaseGame()
	{
		if (window != NULL) 
		{
			delete window;
			window = NULL;
		}

		if (render != NULL)
		{
			delete render;
			render = NULL;
		}
	}
}