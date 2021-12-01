#ifndef PLAYER_H
#define PLAYER_H

#include "exports.h"
#include "Input/input.h"
#include "Sprite/sprite.h"

namespace GameXD
{
	class GRAPHICSENGINE_API Player
	{
	public:
		Player();
		~Player();

		void Init(GL::Render* render, float speed, std::string textureUrl);
		void Update(GL::Input* input, float timer);
		void Draw();
		void DeInit();

	private:
		GL::Sprite* sprite;
		float speed;

		void Inputs(GL::Input* input);
	};
}

#endif // !PLAYER_H
