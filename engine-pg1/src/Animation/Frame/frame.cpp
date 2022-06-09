#include "frame.h"

namespace GL
{
	Frame::Frame()
	{
		uvcords[0] = { 0.f, 0.f };
		uvcords[1] = { 1.f, 0.f };
		uvcords[2] = { 1.f, 1.f };
		uvcords[3] = { 0.f, 1.f };
	}

	Frame::~Frame()
	{
	}

	UVCords* Frame::GetUVCords()
	{
		return uvcords;
	}
}