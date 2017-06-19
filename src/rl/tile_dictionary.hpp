
#ifndef RL_TILE_DICTIONARY_HPP
#define RL_TILE_DICTIONARY_HPP

#include <unordered_map>

#include "tile.hpp"

namespace rl {

template <typename T>
using base_tile_dictionary = std::unordered_map<T, tile::ptr>;

}  // namespace rl

#endif // RL_TILE_DICTIONARY_HPP
