#ifndef SPRITE_H
#define SPRITE_H

#include "Entity/Entity2D/entity2D.h"
#include "Animation/animation.h"
#include "Importer/TextureImporter/textureImporter.h"
#include "Animation/atlasConfig.h"
#include "Material/TextureMaterial/textureMaterial.h"
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
		void Draw() override;
		void DeInit();

		void LoadTexture(const char* path, bool invertImage, TEXTURE_TYPE type);
		void SetTexture(Texture* texture, TEXTURE_TYPE type);

		void AddAnimation(AtlasConfig atlas, float speed);
		void AddAnimation(int rows, int cols, float duration);
		void ChangeAnimation(int index);
		void SetTextureCoordinates(Frame f);

		void SetTransparent(bool transparent);
		bool GetTransparent();

	private:
		SPRITE_TYPE type;
		uint UVB;

		Texture* baseTexture;

		uint uniformBaseTexture;

		int animIndex = 0;
		std::vector<Animation*> anim;
		Frame currFrame;
		bool transparent;

		void SetUniforms() override;
		void UpdateShader() override;
	};
}

#endif // !SPRITE_H