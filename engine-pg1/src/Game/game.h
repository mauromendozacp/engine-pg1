#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include <iostream>

using namespace GL;

namespace GameXD
{
	class GRAPHICSENGINE_API Game : GL::BaseGame
	{
	public:
		Game();
		~Game();
		void Play();

		void Init() override;
		void Update() override;
		void DeInit() override;

	private:
		GL::Shape* shape;
		GL::Sprite* sprite;
		GL::Sprite* rockstar;

		void Inputs();
	};
}

#endif // !GAME_H
