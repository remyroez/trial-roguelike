
#ifndef RL_POINT_HPP
#define RL_POINT_HPP

namespace rl {

struct point {
	int x;
	int y;

	constexpr point operator - () {
		return { -x, -y };
	}

	constexpr point &operator += (const point &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	constexpr point &operator -= (const point &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	constexpr point operator + (const point &rhs) const {
		return { x + rhs.x, y + rhs.y };
	}

	constexpr point operator - (const point &rhs) const {
		return { x - rhs.x, y - rhs.y };
	}

	constexpr bool operator == (const point &rhs) const {
		return (x == rhs.x) && (y == rhs.y);
	}

	constexpr bool operator != (const point &rhs) const {
		return !(*this == rhs);
	}
};

static constexpr point point_zero = { 0, 0 };

}  // namespace rl

#endif // RL_POINT_HPP
