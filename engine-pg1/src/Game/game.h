#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"
#include "Player/player.h"
#include <iostream>

using namespace GL;

namespace GameXD
{
	class GRAPHICSENGINE_API Game : public GL::BaseGame
	{
	public:
		Game();
		~Game();

	protected:
		void Init() override;
		void Update() override;
		void Draw() override;
		void DeInit() override;

	private:
		Player* player;
		GL::Shape* shape;
		GL::Shape* shape2;
		GL::Sprite* rockstar;
	};
}

#endif // !GAME_H
