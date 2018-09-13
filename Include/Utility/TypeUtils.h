#pragma once

#include <type_traits>

namespace winter {

	class TypeUtils final {

	public:

		template<typename T>
		static auto enumValue(T e) {
			return static_cast<std::underlying_type_t<T>>(e);
		}

	private:

		TypeUtils() = default;

	};

}