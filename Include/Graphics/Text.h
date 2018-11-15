#pragma once

#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

#include <memory>

namespace winter {

	class Text final {

	public:

		Text(std::unique_ptr<Mesh> mesh, std::shared_ptr<Texture> texture);

		Mesh& getMesh() const;
		const Texture& getTexture() const;

	private:

		std::unique_ptr<Mesh> mesh;
		std::shared_ptr<Texture> texture;

	};

}