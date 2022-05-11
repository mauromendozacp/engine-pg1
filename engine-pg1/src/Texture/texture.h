#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace GL
{
	enum class TEXTURE_TYPE
	{
		BASE,
		DIFFUSE,
		SPECULAR
	};

	struct Texture
	{
		unsigned int id;
		float width;
		float height;
		std::string type;
		std::string path;
	};
}

#endif // !TEXTURE_H