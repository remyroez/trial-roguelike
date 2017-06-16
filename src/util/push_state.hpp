
#ifndef UTIL_PUSH_STATE_HPP
#define UTIL_PUSH_STATE_HPP

#include <functional>

#include "BearLibTerminal.h"

namespace util {

template <int tCode, class State = int, State tDefaultState = 0>
struct push_state {
	static constexpr int code = tCode;
	using state_t = State;
	using setter_t = std::function<void(state_t)>;

	state_t last_state = tDefaultState;
	setter_t state_setter;

	push_state(state_t state, const setter_t &setter)
	    : last_state(terminal_state(tCode)), state_setter(setter) {
		if (state_setter) state_setter(state);
	}
	~push_state() {
		if (state_setter) state_setter(last_state);
	}
};

struct push_color : public push_state<TK_COLOR, color_t> {
	push_color(color_t color)
	    : push_state(color, static_cast<void (*)(color_t)>(terminal_color)) {}
};

struct push_bkcolor : public push_state<TK_BKCOLOR, color_t> {
	push_bkcolor(color_t color)
	    : push_state(color, static_cast<void (*)(color_t)>(terminal_bkcolor)) {}
};

struct push_layer : public push_state<TK_LAYER> {
	push_layer(int layer) : push_state(layer, terminal_layer) {}
};

struct push_composition : public push_state<TK_COMPOSITION> {
	push_composition(int mode) : push_state(mode, terminal_composition) {}
};

} // namespace util

#endif  // UTIL_PUSH_STATE_HPP
