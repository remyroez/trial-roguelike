
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

	actor(tile::handle tile, const point &position) : _tile(tile), _position(position) {}

	tile::handle tile() const { return _tile; }

	const point &position() const { return _position; }

	void set_position(const rl::point &position) { _position = position; }

	void move(const rl::point &position) { _position += position; }

	int x() const { return position().x; }

	int y() const { return position().y; }

	void set_x(int x) { _position.x = x; }

	void set_y(int y) { _position.y = y; }

	void move_x(int x) { _position.x += x; }

	void move_y(int y) { _position.y += y; }

private:
	tile::handle _tile;
	rl::point _position;
};

}  // namespace rl

#endif // RL_ACTOR_HPP
