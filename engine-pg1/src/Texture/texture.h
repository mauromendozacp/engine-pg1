#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace GL
{
	struct Texture
	{
		unsigned int id;
		float width;
		float height;
		std::string type;
	};
}

#endif // !TEXTURE_H