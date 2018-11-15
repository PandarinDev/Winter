#pragma once

#include "External/glad.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderbuffer.h"

#include <memory>
#include <type_traits>
#include <unordered_map>

namespace winter {

	enum class FramebufferTexture {
		POSITION,
		COLOR,
		NORMAL
	};

	enum class FramebufferRenderbuffer {
		DEPTH
	};

	using FramebufferTextureType = std::underlying_type_t<FramebufferTexture>;
	using FramebufferRenderbufferType = std::underlying_type_t<FramebufferRenderbuffer>;

	struct Framebuffer {

	public:

		Framebuffer(
			GLuint handle,
			std::unordered_map<FramebufferTextureType, std::unique_ptr<Texture>>&& textures,
			std::unordered_map<FramebufferRenderbufferType, std::unique_ptr<Renderbuffer>>&& renderbuffers);
		~Framebuffer();
		Framebuffer(const Framebuffer&) = delete;
		Framebuffer& operator=(const Framebuffer&) = delete;

		GLuint getHandle() const;

	private:

		const GLuint handle;
		std::unordered_map<FramebufferTextureType, std::unique_ptr<Texture>> textures;
		std::unordered_map<FramebufferRenderbufferType, std::unique_ptr<Renderbuffer>> renderbuffers;

	};

}