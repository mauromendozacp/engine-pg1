#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/entity2D.h"
#include "Animation/animation.h"
#include "TextureImporter/textureImporter.h"
#include "Animation/atlasConfig.h"
#include <vector>

namespace GL
{
	class GRAPHICSENGINE_API Sprite : public Entity2D
	{
	public:
		Sprite();
		Sprite(Render* render);
		~Sprite();

		void Init(const char* path, bool invertImage);
		void Update();
		void Draw();

		void AddAnimation(AtlasConfig atlas, float speed);
		void AddAnimation(int rows, int cols, float duration);

	private:
		void SetShader(unsigned int shaderId) override;
		void BindAttrib();
		void BindTexture(Frame f);

		TextureData* textureData;
		Animation* anim;
		Frame currFrame;
	};
}

#endif // !SPRITE_H