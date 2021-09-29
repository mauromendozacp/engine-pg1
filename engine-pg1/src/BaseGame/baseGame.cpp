#include "baseGame.h"

#include "Renderer/renderer.h"
#include "Input/input.h"

namespace GL
{
	BaseGame::BaseGame()
	{
		window = new Window(640, 480, "Hello World");
		render = new Render(window);
		input = new Input(window);
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

		if (input != NULL)
		{
			delete input;
			input = NULL;
		}
	}
}