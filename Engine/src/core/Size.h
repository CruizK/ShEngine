#pragma once

#include <stdint.h>

namespace Shengine {

	struct Size
	{
		uint32_t Width, Height;

		Size(uint32_t width, uint32_t height) :
			Width(width), Height(height)
		{}
	};
}