
#include <functional>
#include <iostream>
#include <string>

#include "BearLibTerminal.h"
#include "libtcod.hpp"

#include "rl/actor.hpp"
#include "rl/tile_dictionary.hpp"
#include "rl/tile_map.hpp"
#include "rl/frame.hpp"
#include "util/push_state.hpp"

namespace {

using tile_dictionary = rl::base_tile_dictionary<std::string>;

tile_dictionary tdic;

rl::tile::handle empty_tile;

inline void render_tile(rl::tile::handle handle, int x = 0, int y = 0) {
	if (auto ptr = handle.lock()) {
		terminal_color(ptr->foreground.argb());
		terminal_bkcolor(ptr->background.argb());
		terminal_put(x, y, ptr->character);

	} else if (auto ptr = empty_tile.lock()) {
		terminal_color(ptr->foreground.argb());
		terminal_bkcolor(ptr->background.argb());
		terminal_put(x, y, ptr->character);
	}
}

inline void render_tile(rl::tile::handle handle, float brightness, int x = 0, int y = 0) {
	if (auto ptr = handle.lock()) {
		terminal_color((ptr->foreground * brightness).argb());
		terminal_bkcolor((ptr->background * brightness).argb());
		terminal_put(x, y, ptr->character);

	} else if (auto ptr = empty_tile.lock()) {
		terminal_color((ptr->foreground * brightness).argb());
		terminal_bkcolor((ptr->background * brightness).argb());
		terminal_put(x, y, ptr->character);
	}
}

inline void render_tile(rl::tile::handle handle, const rl::color light, int x = 0, int y = 0) {
	if (auto ptr = handle.lock()) {
		terminal_color(ptr->foreground.blend(light).argb());
		terminal_bkcolor(ptr->background.blend(light).argb());
		terminal_put(x, y, ptr->character);

	} else if (auto ptr = empty_tile.lock()) {
		terminal_color(ptr->foreground.blend(light).argb());
		terminal_bkcolor(ptr->background.blend(light).argb());
		terminal_put(x, y, ptr->character);
	}
}

void render_tile_map(const rl::tile_map map, int x = 0, int y = 0) {
	for (int i = 0; i < map.width(); i++) {
		for (int j = 0; j < map.height(); j++) {
			if (map.explored(i, j)) {
				render_tile(map.get(i, j), x + i, y + j);
			}
		}
	}
}

void render_tile_map(const rl::tile_map map, std::shared_ptr<TCODMap> tcodmap, int x = 0, int y = 0) {
	for (int i = 0; i < map.width(); i++) {
		for (int j = 0; j < map.height(); j++) {
			if (map.explored(i, j)) {
				render_tile(map.get(i, j), (tcodmap->isInFov(x + i, y + j) ? 1.0f : 0.5f), x + i, y + j);
				//(map.get(i, j), (tcodmap->isInFov(x + i, y + j) ? rl::color_white : rl::color_black), x + i, y + j);
			}
		}
	}
}

void render_tile_map(const rl::tile_map map, const TCODMap &tcodmap, int x = 0, int y = 0) {
	for (int i = 0; i < map.width(); i++) {
		for (int j = 0; j < map.height(); j++) {
			if (map.explored(i, j)) {
				render_tile(map.get(i, j), (tcodmap.isInFov(x + i, y + j) ? 1.0f : 0.5f), x + i, y + j);
				//render_tile(map.get(i, j), (tcodmap.isInFov(x + i, y + j) ? rl::color_white : rl::color_black), x + i, y + j);
			}
		}
	}
}

void render_frame(const rl::frame frame, const rl::rect rect) {
	for (int i = 0; i < rect.width; i++) {
		for (int j = 0; j < rect.height; j++) {
			rl::symbol_t symbol = frame.space;

			if (i == 0) {
				if (j == 0) {
					symbol = frame.top_left;

				} else if (j == rect.height - 1) {
					symbol = frame.bottom_left;

				} else {
					symbol = frame.left;
				}

			} else if (i == rect.width - 1) {
				if (j == 0) {
					symbol = frame.top_right;

				} else if (j == rect.height - 1) {
					symbol = frame.bottom_right;

				} else {
					symbol = frame.right;
				}

			} else if (j == 0) {
				symbol = frame.top;

			} else if (j == rect.height - 1) {
				symbol = frame.bottom;
			}

			terminal_put(
				rect.x + i,
				rect.y + j,
				symbol
			);
		}
	}
}

void read_map(const rl::tile_map &tilemap, std::shared_ptr<TCODMap> tcodmap) {
	for (int i = 0; i < tilemap.width(); i++) {
		for (int j = 0; j < tilemap.height(); j++) {
			auto handle = tilemap.get(i, j);
			if (auto ptr = handle.lock()) {
				tcodmap->setProperties(i, j, ptr->transparent, ptr->walkable);
			}
		}
	}
}

void read_map(const rl::tile_map &tilemap, TCODMap &tcodmap) {
	for (int i = 0; i < tilemap.width(); i++) {
		for (int j = 0; j < tilemap.height(); j++) {
			auto handle = tilemap.get(i, j);
			if (auto ptr = handle.lock()) {
				tcodmap.setProperties(i, j, ptr->transparent, ptr->walkable);
			}
		}
	}
}

void explore_map(rl::tile_map &tilemap, const TCODMap &tcodmap) {
	for (int i = 0; i < tilemap.width(); i++) {
		for (int j = 0; j < tilemap.height(); j++) {
			if (!tilemap.explored(i, j)) {
				tilemap.set_explored(i, j, tcodmap.isInFov(i, j));
			}
		}
	}
}

}

TERMINAL_TAKE_CARE_OF_WINMAIN

void test_frame() {
	using namespace rl;

	render_frame(frame(), rect(1, 1, 10, 10));
	render_frame(frame(), rect(3, 3, 10, 10));
	render_frame(frame(), rect(5, 5, 10, 10));
}

void test_tile_map() {
	using namespace rl;

	tile_map map(20, 20, tdic.at("wall"));

	tile_map room(10, 5, tdic.at("floor"));

	map.merge(room, 3, 3);
	map.merge(room, 5, 10);

	render_tile_map(map, 3, 3);

	auto view = map.get(0, 0, 5, 5);

	render_tile_map(view, 25, 3);
}

void test_push_state() {
	using namespace util;

	terminal_color(0xFFFFFFFF);

	terminal_print(0, 0, "abcde");

	{
		push_color color(0xFFFF00FF);
		push_layer layer(1);

		terminal_print(0, 0, "_____");

		{
			push_color color(0xFF0000FF);
			terminal_print(0, 1, "@@@@@");
		}
		terminal_print(0, 2, "abc");
	}
	terminal_print(2, 0, "vwxyz");
}

void test_fov() {
	auto tcodmap = std::make_shared<TCODMap>(20, 20);

	rl::tile_map map(20, 20, ::tdic.at("wall"));
	map.set({ 1, 1, 5, 5 }, ::tdic.at("floor"));
	map.set(4, 4, ::tdic.at("wall"));
	map.set(4, 3, ::tdic.at("wall"));

	read_map(map, tcodmap);

	tcodmap->computeFov(5, 5, 5, false, FOV_DIAMOND);

	render_tile_map(map, tcodmap);
}

void update_viewport(rl::tile_map &map, rl::actor &you, rl::rect &viewport) {
	viewport.x = you.x() - viewport.width / 2;
	viewport.y = you.y() - viewport.height / 2;

	auto view = map.get(viewport);
	TCODMap fov(viewport.width, viewport.height);
	read_map(view, fov);

	auto local_pos = rl::point{ viewport.width / 2, viewport.height / 2 };
	fov.computeFov(local_pos.x, local_pos.y, 0, true, FOV_DIAMOND);

	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			auto x = local_pos.x + i;
			auto y = local_pos.y + j;
			if (x < 0) {

			} else if (y < 0) {

			} else if (x >= fov.getWidth()) {

			} else if (y >= fov.getHeight()) {

			} else {
				fov.setInFov(x, y, true);
			}
		}
	}

	explore_map(view, fov);
	map.merge_explored(view, viewport.x, viewport.y);

	render_tile_map(view, fov, 0, 0);

	render_tile(you.tile(), 0 + you.x() - viewport.x, 0 + you.y() - viewport.y);
}

int main() {
	terminal_open();

	// Printing text
	terminal_set("window: size=80x45, cellsize=16x16, title='Roguelike'");

	//terminal_set("jpn font: ./asset/misaki_gothic.ttf, size=8x8, hinting=none");
	//terminal_set("font: ./asset/terminal8x8_gs_ro.png, size=8x8");
	//terminal_set("font: ./asset/terminal16x16_gs_ro.png, size=16x16");
	//terminal_set("font: ./asset/terminal8x12_gs_ro.png, size=8x12");
	terminal_set("font: ./asset/16x16_sm_ascii.png, size=16x16");

	//terminal_color("gray");

	::tdic.emplace("you", std::make_shared<rl::tile>(U'@', rl::color_red, rl::color_transparent));

	::tdic.emplace("wall", std::make_shared<rl::tile>(0xB2, rl::color_white, rl::color_silver, false, false));
	::tdic.emplace("floor", std::make_shared<rl::tile>(U'.', rl::color_gray, rl::color_black));
	::tdic.emplace("tree", std::make_shared<rl::tile>(0x05, rl::color_green, rl::color_maroon, false, true));
	::tdic.emplace("water", std::make_shared<rl::tile>(U'~', rl::color_teal, rl::color_navy, true, false));

	::empty_tile = tdic.at("wall");

	rl::tile_map map(50, 50, tdic.at("wall"));
	map.set({ 1, 1, 5, 5 }, tdic.at("floor"));
	map.set({ 7, 1, 8, 8 }, tdic.at("floor"));
	map.set({ 16, 1, 12, 12 }, tdic.at("floor"));

	map.set({ 1, 3, 6, 1 }, tdic.at("floor"));
	map.set({ 8, 5, 10, 1 }, tdic.at("floor"));

	map.set({ 20, 5, 5, 5 }, tdic.at("tree"));

	map.set({ 23, 3, 1, 10 }, tdic.at("water"));

	rl::rect viewport = { 0, 0, 45, 45 };

	rl::actor you(tdic.at("you"), {3, 3});

	update_viewport(map, you, viewport);

	terminal_refresh();

	bool running = true;
	while (running) {
		auto key = terminal_read();
		bool released = (key & TK_KEY_RELEASED) != 0;
		key = key & 0xFF;

		bool update = false;

		auto move_position = you.position();

		switch (key) {
		case TK_ESCAPE:
		case TK_CLOSE:
			running = false;
			break;

		case TK_UP:
		case TK_KP_8: 
			move_position.y -= 1;
			break;

		case TK_DOWN:
		case TK_KP_2:
			move_position.y += 1;
			break;

		case TK_LEFT:
		case TK_KP_4:
			move_position.x -= 1;
			break;

		case TK_RIGHT:
		case TK_KP_6:
			move_position.x += 1;
			break;

		case TK_KP_7:
		case TK_HOME:
			move_position.x -= 1;
			move_position.y -= 1;
			break;

		case TK_KP_9:
		case TK_PAGEUP:
			move_position.x += 1;
			move_position.y -= 1;
			break;

		case TK_KP_1:
		case TK_END:
			move_position.x -= 1;
			move_position.y += 1;
			break;

		case TK_KP_3:
		case TK_PAGEDOWN:
			move_position.x += 1;
			move_position.y += 1;
			break;
		}

		if (you.position() != move_position) {
			if (map.get(move_position.x, move_position.y).lock()->walkable) {
				you.set_position(move_position);
			}
			update = true;
		}

		if (update) {
			terminal_clear();
			update_viewport(map, you, viewport);
			terminal_refresh();
		}
	}

	terminal_close();
}
