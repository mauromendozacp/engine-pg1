#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/entity2D.h"
#include "Animation/animation.h"
#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Sprite : public Entity2D
	{
	public:
		Sprite(Render* render);
		~Sprite();

		void Init(std::string path);
		void Update(float timer);
		void Draw();

		void AddAnimation(int rows, int cols);

	private:
		void LoadTexture(std::string path);
		void SetShader(unsigned int shaderId) override;
		void BindAttrib();

		unsigned int textureId;
		int width, height;
		Animation* anim;
		Frame currFrame;
	};
}

#endif // !SPRITE_H