#include "Graphics/Text.h"

namespace winter {

	Text::Text(std::unique_ptr<Mesh> mesh, std::shared_ptr<Texture> texture) :
		mesh(std::move(mesh)), texture(texture) {}

	const Mesh& Text::getMesh() const {
		return *mesh;
	}

	const Texture& Text::getTexture() const {
		return *texture;
	}

}