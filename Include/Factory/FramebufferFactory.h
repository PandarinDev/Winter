#pragma once

#include "Graphics/Framebuffer.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderbuffer.h"

#include <memory>

namespace winter {

	struct FramebufferFactory final {

		static std::unique_ptr<Framebuffer> createGBuffer(int width, int height);

	private:

		static std::unique_ptr<Texture> createTextureForFramebuffer(GLuint fbo, int width, int height, int attachmentLevel);
		static std::unique_ptr<Renderbuffer> createDepthBufferForFramebuffer(GLuint fbo, int width, int height);

		FramebufferFactory() = default;

	};

}