
#ifndef RL_FRAME_HPP
#define RL_FRAME_HPP

#include <array>

#include "symbol.hpp"
#include "rect.hpp"

namespace rl {

struct frame {
	static constexpr size_t num_frame_symbols = 9;
	using frame_symbols_t = std::array<symbol_t, num_frame_symbols>;

	union {
		frame_symbols_t symbols;
		struct {
			symbol_t top_left;
			symbol_t top;
			symbol_t top_right;

			symbol_t left;
			symbol_t space;
			symbol_t right;

			symbol_t bottom_left;
			symbol_t bottom;
			symbol_t bottom_right;
		};
	};

	frame(
		frame_symbols_t symbols
	) : symbols(symbols) {}

	frame(
		symbol_t top_left,
		symbol_t top,
		symbol_t top_right,
		symbol_t left,
		symbol_t space,
		symbol_t right,
		symbol_t bottom_left,
		symbol_t bottom,
		symbol_t bottom_right
	) : 
		top_left(top_left),
		top(top),
		top_right(top_right),
		left(left),
		space(space),
		right(right),
		bottom_left(bottom_left),
		bottom(bottom),
		bottom_right(bottom_right)
	{}

	frame() : frame(
		U'+', U'-', U'+',
		U'|', U' ', U'|',
		U'+', U'-', U'+'
	) {}
};

}  // namespace rl

#endif // RL_FRAME_HPP
