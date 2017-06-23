
#ifndef RL_POINT_HPP
#define RL_POINT_HPP

namespace rl {

struct point {
	int x;
	int y;

	point operator - () {
		return { -x, -y };
	}

	point &operator += (const point &rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	point &operator -= (const point &rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	point operator + (const point &rhs) const {
		return { x + rhs.x, y + rhs.y };
	}

	point operator - (const point &rhs) const {
		return { x - rhs.x, y - rhs.y };
	}

	bool operator == (const point &rhs) const {
		return (x == rhs.x) && (y == rhs.y);
	}

	bool operator != (const point &rhs) const {
		return !(*this == rhs);
	}
};

}  // namespace rl

#endif // RL_POINT_HPP
