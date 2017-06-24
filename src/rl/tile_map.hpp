
#ifndef RL_TILE_MAP_HPP
#define RL_TILE_MAP_HPP

#include <vector>
#include <algorithm>
#include <cassert>

#include "tile.hpp"
#include "rect.hpp"
#include "point.hpp"

namespace rl {

class tile_map {
public:
	using tile_container = std::vector<tile::handle>;
	using explore_set = std::vector<bool>;

	tile_map(int w, int h) : _width(w), _height(h) {
		resize();
	}

	tile_map(int w, int h, tile::handle tile) : tile_map(w, h) {
		fill(tile);
	}

	tile_map(const tile_map &map) = default;

	int width() const { return _width; }
	int height() const { return _height; }

	void set_width(int w) {
		_width = w;
		resize();
	}

	void set_height(int h) {
		_height = h;
		resize();
	}

	void resize(int size) {
		_tiles.resize(size);
		_explored.resize(size);
	}

	void resize() {
		resize(_width * _height);
	}

	void resize(int w, int h) {
		_width = w;
		_height = h;
		resize();
	}

	void fill(tile::handle tile) {
		std::fill(_tiles.begin(), _tiles.end(), tile);
		std::fill(_explored.begin(), _explored.end(), false);
	}

	bool explored(size_t index) const {
		assert(index < _explored.size());
		return _explored[index];
	}

	bool explored(int x, int y) const {
		assert(x >= 0);
		assert(y >= 0);
		assert(x < width());
		assert(y < height());
		return explored(y * width() + x);
	}

	void set_explored(size_t index, bool explore) {
		if (index >= _explored.size()) {
			// index over

		} else {
			_explored[index] = explore;
		}
	}

	void set_explored(int x, int y, bool explore) {
		if (x >= width()) {
			// x over

		} else if (y >= height()) {
			// y over

		} else {
			set_explored(y * width() + x, explore);
		}
	}

	void set_explored(const point &pos, bool explore) {
		set_explored(pos.x, pos.y, explore);
	}

	tile::handle get(size_t index) const {
		assert(index < _tiles.size());
		return _tiles[index];
	}

	tile::handle get(int x, int y) const {
		assert(x >= 0);
		assert(y >= 0);
		assert(x < width());
		assert(y < height());
		return get(y * width() + x);
	}

	tile::handle get(const point &pos) const {
		return get(pos.x, pos.y);
	}

	tile_map get(int x, int y, int w, int h) const {
		tile_map map(w, h);

		for (int i = 0; i < map.width(); i++) {
			for (int j = 0; j < map.height(); j++) {
				auto gx = (x + i);
				auto gy = (y + j);
				if (gx >= width()) {
					// over width

				} else if (gy >= height()) {
					// over height

				} else if (gx < 0) {
					// over width

				} else if (gy < 0) {
					// over height

				} else {
					map.set(i, j, get(x + i, y + j));
					map.set_explored(i, j, explored(x + i, y + j));
				}
			}
		}

		return map;
	}

	tile_map get(const rect &rect) const {
		return get(rect.x, rect.y, rect.width, rect.height);
	}

	void set(size_t index, tile::handle tile) {
		if (index >= _tiles.size()) {
			// index over
		} else {
			_tiles[index] = tile;
		}
	}

	void set(int x, int y, tile::handle tile) {
		if (x >= width()) {
			// x over

		} else if (y >= height()) {
			// y over

		} else {
			set(y * width() + x, tile);
		}
	}

	void set(const point &pos, tile::handle tile) {
		set(pos.x, pos.y, tile);
	}

	void set(const rect &rect, tile::handle tile) {
		for (int i = 0; i < rect.width; i++) {
			for (int j = 0; j < rect.height; j++) {
				set(rect.x + i, rect.y + j, tile);
			}
		}
	}

	void merge(const tile_map &map, int x = 0, int y = 0) {
		for (int i = 0; i < map.width(); i++) {
			for (int j = 0; j < map.height(); j++) {
				set(x + i, y + j, map.get(i, j));
				if (map.explored(i, j)) set_explored(x + i, y + j, map.explored(i, j));
			}
		}
	}

	void merge(const tile_map &map, const point &pos) {
		merge(map, pos.x, pos.y);
	}

	void merge_explored(const tile_map &map, int x = 0, int y = 0) {
		for (int i = 0; i < map.width(); i++) {
			for (int j = 0; j < map.height(); j++) {
				if (map.explored(i, j)) set_explored(x + i, y + j, map.explored(i, j));
			}
		}
	}

	void merge_explored(const tile_map &map, const point &pos) {
		merge_explored(map, pos.x, pos.y);
	}

	const tile_container &tiles() const { return _tiles; }

	const explore_set &explores() const { return _explored; }

private:
	int _width;
	int _height;
	tile_container _tiles;
	explore_set _explored;
};

}  // namespace rl

#endif // RL_TILE_MAP_HPP
