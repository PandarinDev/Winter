#include "Factory/FramebufferFactory.h"
#include "Utility/TypeUtils.h"

#include <stdexcept>

namespace winter {

	std::unique_ptr<Framebuffer> FramebufferFactory::createGBuffer(int width, int height) {
		GLuint handle;
		glCreateFramebuffers(1, &handle);
		auto positionTexture = createTextureForFramebuffer(handle, width, height, 0);
		auto normalTexture = createTextureForFramebuffer(handle, width, height, 1);
		auto colorTexture = createTextureForFramebuffer(handle, width, height, 2);
		auto depthBuffer = createDepthBufferForFramebuffer(handle, width, height);
		GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glNamedFramebufferDrawBuffers(handle, 3, attachments);
		if (glCheckNamedFramebufferStatus(handle, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			throw std::runtime_error("Failed to create framebuffer.");
		}

		std::unordered_map<FramebufferTextureType, std::unique_ptr<Texture>> textures;
		textures.emplace(TypeUtils::enumValue(FramebufferTexture::POSITION), std::move(positionTexture));
		textures.emplace(TypeUtils::enumValue(FramebufferTexture::NORMAL), std::move(normalTexture));
		textures.emplace(TypeUtils::enumValue(FramebufferTexture::COLOR), std::move(colorTexture));

		std::unordered_map<FramebufferRenderbufferType, std::unique_ptr<Renderbuffer>> renderbuffers;
		renderbuffers.emplace(TypeUtils::enumValue(FramebufferRenderbuffer::DEPTH), std::move(depthBuffer));
		return std::make_unique<Framebuffer>(handle, std::move(textures), std::move(renderbuffers));
	}

	std::unique_ptr<Texture> FramebufferFactory::createTextureForFramebuffer(GLuint fbo, int width, int height, int attachmentLevel) {
		GLuint texture;
		glCreateTextures(GL_TEXTURE_2D, 1, &texture);
		glTextureStorage2D(texture, 1, GL_RGBA8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glNamedFramebufferTexture(fbo, GL_COLOR_ATTACHMENT0 + attachmentLevel, texture, 0);
		return std::make_unique<Texture>(texture, width, height);
	}

	std::unique_ptr<Renderbuffer> FramebufferFactory::createDepthBufferForFramebuffer(GLuint fbo, int width, int height) {
		GLuint renderbuffer;
		glCreateRenderbuffers(1, &renderbuffer);
		glNamedRenderbufferStorage(renderbuffer, GL_DEPTH24_STENCIL8, width, height);
		glNamedFramebufferRenderbuffer(fbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
		return std::make_unique<Renderbuffer>(renderbuffer);
	}

}