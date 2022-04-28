#ifndef SPRITE_H
#define SPRITE_H

#include "Entity2D/entity2D.h"
#include "Animation/animation.h"
#include "TextureImporter/textureImporter.h"
#include "Animation/atlasConfig.h"
#include <vector>

namespace GL
{
	enum class SPRITE_TYPE
	{
		QUAD,
		CUBE
	};

	class GRAPHICSENGINE_API Sprite : public Entity2D
	{
	public:
		Sprite();
		Sprite(Render* render);
		~Sprite();

		void Init(SPRITE_TYPE type);
		void Update();
		void Draw();
		void DeInit();

		void SetTexture(TextureData* texture);
		void LoadTexture(const char* path, bool invertImage);
		void AddAnimation(AtlasConfig atlas, float speed);
		void AddAnimation(int rows, int cols, float duration);
		void ChangeAnimation(int index);
		void SetTextureCoordinates(Frame f);

		void SetTransparent(bool transparent);
		bool GetTransparent();

	private:
		SPRITE_TYPE type;

		TextureData* textureData;

		uint uniformTexture;
		uint UVB;

		int animIndex = 0;
		std::vector<Animation*> anim;
		Frame currFrame;
		bool transparent;

		void SetUniforms(uint shaderId);
	};
}

#endif // !SPRITE_H