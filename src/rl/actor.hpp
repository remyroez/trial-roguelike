
#ifndef RL_ACTOR_HPP
#define RL_ACTOR_HPP

#include <memory>

#include "point.hpp"
#include "tile.hpp"

namespace rl {

class actor {
public:
	using this_t = actor;
	using pointer = std::shared_ptr<this_t>;
	using handle = std::weak_ptr<this_t>;

	template <typename... Args>
	static pointer make(Args&&... args) {
		return std::make_shared<this_t>(std::forward<Args>(args)...);
	}

	actor() = default;

	actor(tile::handle tile, const point &point) : _tile(tile), _point(point) {}

	tile::handle tile() const { return _tile; }

	const point &point() const { return _point; }

	void set_point(const rl::point &point) { _point = point; }

	void move(const rl::point &point) { _point += point; }

	int x() const { return point().x; }

	int y() const { return point().y; }

	void set_x(int x) { _point.x = x; }

	void set_y(int y) { _point.y = y; }

	void move_x(int x) { _point.x += x; }

	void move_y(int y) { _point.y += y; }

private:
	tile::handle _tile;
	rl::point _point;
};

}  // namespace rl

#endif // RL_ACTOR_HPP
