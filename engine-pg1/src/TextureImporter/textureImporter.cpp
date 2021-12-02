#include "textureImporter.h"
#include "StbImage/stb_image.h"

namespace GL
{
	TextureImporter::TextureImporter()
	{
	}

	TextureImporter::~TextureImporter()
	{
	}

	TextureData TextureImporter::LoadTexture(const char* path, bool invertImage)
	{
		unsigned int textureId;
		int textureWidth;
		int textureHeight;
		int nrChannels;

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load and generate the texture
		stbi_set_flip_vertically_on_load(invertImage);
		unsigned char* data = stbi_load(path, &textureWidth, &textureHeight, &nrChannels, 0);
		if (data)
		{
			int channelType = GL_RGB;
			switch (nrChannels)
			{
			case 1:
				channelType = GL_R;
				break;
			case 2:
				channelType = GL_RG;
				break;
			case 3:
				channelType = GL_RGB;
				break;
			case 4:
				channelType = GL_RGBA;
				break;
			default:
				break;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, channelType, textureWidth, textureHeight, 0, channelType, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		return TextureData{ textureId, (float)textureWidth, (float)textureHeight };
	}
}