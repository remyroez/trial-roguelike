
#ifndef RL_COLOR_HPP
#define RL_COLOR_HPP

namespace rl {

struct color {
	union {
		int value[4];
		struct {
			int r;
			int g;
			int b;
			int a;
		};
	};

	using code_t = unsigned int;

	constexpr color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}
	constexpr color() : color(0, 0, 0, 0xFF) {}

	constexpr code_t rgb() const { return (r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF); }
	constexpr code_t rgba() const { return rgb() << 8 | (a & 0xFF); }
	constexpr code_t argb() const { return rgb() | (a & 0xFF) << 24; }
};

}  // namespace rl

#endif // RL_COLOR_HPP
