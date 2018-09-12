#pragma once

#include "External/glad.h"

#include <string>

namespace winter {

	class OGLUtils final {

	public:

		static std::string translateErrorCode(GLenum error);

	private:

		OGLUtils() = default;

	};

}