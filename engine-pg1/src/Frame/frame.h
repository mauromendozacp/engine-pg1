#ifndef FRAME_H
#define FRAME_H

#include "exports.h"

namespace GL
{
	struct UVCords
	{
		float u, v;
	};

	class Frame
	{
	public:
		Frame();
		~Frame();
		UVCords* GetUVCords();

	private:
		UVCords uvcords[4];
	};
}

#endif // !FRAME_H