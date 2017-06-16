
#ifndef RL_TILE_HPP
#define RL_TILE_HPP

#include "symbol.hpp"

namespace rl {

struct tile {
	symbol_t symbol;

	tile(symbol_t symbol = U'#') : symbol(symbol) {}
};

}  // namespace rl

#endif // RL_TILE_HPP
