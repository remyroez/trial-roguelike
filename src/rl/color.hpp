
#ifndef RL_COLOR_HPP
#define RL_COLOR_HPP

#include <type_traits>
#include <algorithm>

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
	constexpr color(int r, int g, int b) : color(r, g, b, 0xFF) {}
	constexpr color(int gray) : color(gray, gray, gray) {}
	constexpr color() : color(0, 0, 0) {}

	constexpr int red() const { return std::max(0, std::min(r, 0xFF)) & 0xFF; }
	constexpr int green() const { return std::max(0, std::min(g, 0xFF)) & 0xFF; }
	constexpr int blue() const { return std::max(0, std::min(b, 0xFF)) & 0xFF; }
	constexpr int alpha() const { return std::max(0, std::min(a, 0xFF)) & 0xFF; }

	constexpr code_t rgb() const { return (red() << 16) | (green() << 8) | blue(); }
	constexpr code_t rgba() const { return rgb() << 8 | alpha(); }
	constexpr code_t argb() const { return (alpha() << 24) | rgb(); }
	constexpr code_t bgr() const { return (blue() << 16) | (green() << 8) | red(); }
	constexpr code_t bgra() const { return bgr() << 8 | alpha(); }
	constexpr code_t abgr() const { return (alpha() << 24) | bgr(); }

	constexpr color clamp() const { return { red(), green(), blue(), alpha() }; }

	constexpr color blend(const color &rhs) const {
		auto blended = ((*this) + rhs) * 0.5f;
		blended.a = a;
		return blended;
	}

	constexpr color alpha_blend(const color &rhs) const {
		return ((*this) + rhs) * 0.5f;
	}

	constexpr color operator - () const {
		return { -r, -g, -b, -a };
	}

	constexpr color &operator += (const color &rhs) {
		r += rhs.r;
		g += rhs.g;
		b += rhs.b;
		a += rhs.a;
		return *this;
	}

	constexpr color &operator -= (const color &rhs) {
		r -= rhs.r;
		g -= rhs.g;
		b -= rhs.b;
		a -= rhs.a;
		return *this;
	}

	constexpr color operator + (const color &rhs) const {
		return { r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
	}

	constexpr color operator - (const color &rhs) const {
		return { r - rhs.r, g - rhs.g, b - rhs.b, a - rhs.a };
	}

	template <typename T>
	constexpr color operator * (T s) const {
		static_assert(std::is_arithmetic<T>::value, "Arithmetic required.");
		return { static_cast<int>(r * s), static_cast<int>(g * s), static_cast<int>(b * s), static_cast<int>(a * s) };
	}

	template <typename T>
	constexpr color operator / (T s) const {
		static_assert(std::is_arithmetic<T>::value, "Arithmetic required.");
		return { static_cast<int>(r / s), static_cast<int>(g / s), static_cast<int>(b / s), static_cast<int>(a / s) };
	}

	constexpr static color make_from_rgba(code_t rgba) {
		return { (rgba >> 24) & 0xFF, (rgba >> 16) & 0xFF, (rgba >> 8) & 0xFF, (rgba & 0xFF) };
	}

	constexpr static color make_from_argb(code_t argb) {
		return { (argb >> 16) & 0xFF, (argb >> 8) & 0xFF, (argb >> 0) & 0xFF, (argb >> 24) & 0xFF };
	}
};

static constexpr color color_black = { 0, 0, 0 };

static constexpr color color_gray = { 0x80, 0x80, 0x80 };

static constexpr color color_silver = { 0xC0, 0xC0, 0xC0 };

static constexpr color color_white = { 0xFF, 0xFF, 0xFF };

static constexpr color color_red = { 0xFF, 0, 0 };

static constexpr color color_maroon = { 0x80, 0, 0 };

static constexpr color color_lime = { 0, 0xFF, 0 };

static constexpr color color_green = { 0, 0x80, 0 };

static constexpr color color_blue = { 0, 0, 0xFF };

static constexpr color color_navy = { 0, 0, 0x80 };

static constexpr color color_yellow = { 0xFF, 0xFF, 0 };

static constexpr color color_olive = { 0x80, 0x80, 0 };

static constexpr color color_magenta = { 0xFF, 0, 0xFF };

static constexpr color color_purple = { 0x80, 0, 0x80 };

static constexpr color color_cyan = { 0, 0xFF, 0xFF };

static constexpr color color_teal = { 0, 0x80, 0x80 };

static constexpr color color_transparent = { 0, 0, 0, 0 };

}  // namespace rl

#endif // RL_COLOR_HPP
