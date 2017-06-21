
#ifndef RL_TILE_MAP_HPP
#define RL_TILE_MAP_HPP

#include <vector>
#include <algorithm>
#include <cassert>

#include "tile.hpp"
#include "rect.hpp"

namespace rl {

class tile_map {
public:
	using tile_list = std::vector<tile::handle>;

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

	void resize() {
		_tiles.resize(_width * _height);
	}

	void resize(int w, int h) {
		_width = w;
		_height = h;
		resize();
	}

	void fill(tile::handle tile) {
		std::fill(_tiles.begin(), _tiles.end(), tile);
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
		}
		else {
			_tiles[index] = tile;
		}
	}

	void set(int x, int y, tile::handle tile) {
		if (x >= width()) {
			// x over
		}
		else if (y >= height()) {
			// y over
		}
		else {
			set(y * width() + x, tile);
		}
	}

	void set(const rect &rect, tile::handle tile) {
		for (int i = 0; i < rect.width; i++) {
			for (int j = 0; j < rect.height; j++) {
				set(rect.x + i, rect.y + j, tile);
			}
		}
	}

	void set(const tile_map &map, int x = 0, int y = 0) {
		for (int i = 0; i < map.width(); i++) {
			for (int j = 0; j < map.height(); j++) {
				set(x + i, y + j, map.get(i, j));
			}
		}
	}

	const tile_list &tiles() const { return _tiles; }

private:
	int _width;
	int _height;
	tile_list _tiles;

};

}  // namespace rl

#endif // RL_TILE_MAP_HPP
