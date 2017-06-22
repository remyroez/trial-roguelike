
#ifndef RL_TILE_HPP
#define RL_TILE_HPP

#include <memory>

#include "symbol.hpp"
#include "color.hpp"

namespace rl {

struct tile {
	using pointer = std::shared_ptr<tile>;
	using handle = std::weak_ptr<tile>;

	color foreground = color_white;
	color background = color_black;

	symbol_t character = 0;
	symbol_t graphic = 0;

	bool transparent = true;
	bool walkable = true;

	tile() = default;

	tile(
		symbol_t character,
		symbol_t graphic,
		const rl::color &color,
		const rl::color &bkcolor,
		bool transparent = true,
		bool walkable = true
	) : character(character), graphic(graphic), foreground(color), background(bkcolor), transparent(transparent), walkable(walkable) {}

	tile(
		symbol_t character,
		bool transparent = true,
		bool walkable = true
	) : tile(character, 0, color_white, color_black, transparent, walkable) {}

	tile(
		symbol_t character,
		const rl::color &color,
		const rl::color &bkcolor,
		bool transparent = true,
		bool walkable = true
	) : tile(character, 0, color, bkcolor, transparent, walkable) {}

	tile(
		symbol_t character,
		const rl::color &color,
		bool transparent = true,
		bool walkable = true
	) : tile(character, color, color_black, transparent, walkable) {}
};

}  // namespace rl

#endif // RL_TILE_HPP
