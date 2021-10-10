#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/entity2D.h"

namespace GL
{
	class GRAPHICSENGINE_API Sprite : public Entity2D
	{
	public:
		Sprite(Render* render);
		~Sprite();

		void Init(std::string path);
		void Draw();

	private:
		void LoadTexture(std::string path);
		void SetShader(unsigned int shaderId) override;
		void BindAttrib();

		unsigned int textureId;
	};
}

#endif // !SPRITE_H