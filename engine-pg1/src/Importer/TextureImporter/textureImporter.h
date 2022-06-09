#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "exports.h"

#include "Texture/texture.h"

#include "StbImage/stb_image.h"

#include <iostream>

namespace GL
{
	class GRAPHICSENGINE_API TextureImporter
	{
	public:
		TextureImporter();
		~TextureImporter();

		static Texture LoadTexture(const char* path, bool invertImage);

	private:

	};
}

#endif // !TEXTURE_IMPORTER_H