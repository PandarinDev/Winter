#include "Graphics/Framebuffer.h"

namespace winter {

	Framebuffer::Framebuffer(
		GLuint handle,
		std::unordered_map<FramebufferTextureType, std::unique_ptr<Texture>>&& textures,
		std::unordered_map<FramebufferRenderbufferType, std::unique_ptr<Renderbuffer>>&& renderbuffers) :
		handle(handle), textures(std::move(textures)), renderbuffers(std::move(renderbuffers)) {}

	Framebuffer::~Framebuffer() {
		glDeleteFramebuffers(1, &handle);
	}

	GLuint Framebuffer::getHandle() const {
		return handle;
	}

}