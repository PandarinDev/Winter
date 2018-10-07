#pragma once

#include <cstdio>

namespace winter {

	struct ObjVertex final {
		std::size_t vertex;
		std::size_t uv;
		std::size_t normal;
	};

}