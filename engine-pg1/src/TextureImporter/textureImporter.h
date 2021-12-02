#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "exports.h"
#include <iostream>

namespace GL
{
	struct TextureData
	{
		unsigned int id;
		float width;
		float height;
	};

	class GRAPHICSENGINE_API TextureImporter
	{
	public:
		TextureImporter();
		~TextureImporter();

		static TextureData LoadTexture(const char* path, bool invertImage);

	private:

	};
}

#endif // !TEXTURE_IMPORTER_H