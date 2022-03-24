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

		void Init();
		void Update();
		void Draw();
		void DeInit();

		void SetTexture(TextureData* texture);
		void LoadTexture(const char* path, bool invertImage);
		void AddAnimation(AtlasConfig atlas, float speed);
		void AddAnimation(int rows, int cols, float duration);
		void ChangeAnimation(int index);
		void SetTextureCoordinates(Frame f);
		void SetTextureCoordinates(float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4);

	private:
		float textureVertex[textureTamVert]
		{
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left 
		};

		uint uniformTexture;

		TextureData* textureData;
		int animIndex = 0;
		std::vector<Animation*> anim;
		Frame currFrame;

		void SetUniforms();
	};
}

#endif // !SPRITE_H