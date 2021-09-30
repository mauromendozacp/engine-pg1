#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"

namespace GL
{
	class GRAPHICSENGINE_API Game : BaseGame
	{
	public:
		Game();
		~Game();
		void Play();

		void Init() override;
		void Update() override;
		void DeInit() override;

	private:
		Shape* entity;
	};
}

#endif // !GAME_H
