#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/entity2D.h"
#include "Animation/animation.h"
#include "TextureImporter/textureImporter.h"
#include "Animation/atlasConfig.h"
#include <vector>

namespace GL
{
	const int textureTamVert = 32;
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
		void ChangeAnimation(int index);

	private:
		float textureVertex[textureTamVert]
		{
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
		};

		void SetShader(unsigned int shaderId) override;
		void BindAttrib();
		void BindTexture(Frame f);

		TextureData* textureData;
		int animIndex = 0;
		std::vector<Animation*> anim;
		Frame currFrame;
	};
}

#endif // !SPRITE_H