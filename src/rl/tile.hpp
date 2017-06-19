
#ifndef RL_TILE_HPP
#define RL_TILE_HPP

#include <memory>

#include "symbol.hpp"

namespace rl {

struct tile {
	using ptr = std::shared_ptr<tile>;
	using handle = std::weak_ptr<tile>;

	symbol_t character = 0;
	symbol_t graphic = 0;

	bool transparent = true;
	bool walkable = true;

	tile() = default;

	tile(
		symbol_t character,
		symbol_t graphic,
		bool transparent = true,
		bool walkable = true
	) : character(character), graphic(graphic), transparent(transparent), walkable(walkable) {}

	tile(
		symbol_t character,
		bool transparent = true,
		bool walkable = true
	) : tile(character, 0, transparent, walkable) {}
};

}  // namespace rl

#endif // RL_TILE_HPP
