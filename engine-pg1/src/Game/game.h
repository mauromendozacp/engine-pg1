#ifndef GAME_H
#define GAME_H

#include "BaseGame/baseGame.h"

namespace GameXD
{
	class GRAPHICSENGINE_API Game : GL::BaseGame
	{
	public:
		Game();
		~Game();
		void Play();
		void Inputs();

		void Init() override;
		void Update() override;
		void DeInit() override;

	private:
		GL::Shape* shape;
	};
}

#endif // !GAME_H
