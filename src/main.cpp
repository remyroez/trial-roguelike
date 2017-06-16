
#include <functional>
#include <iostream>

#include "BearLibTerminal.h"
#include "libtcod.hpp"

#include "rl/tile_map.hpp"
#include "rl/frame.hpp"
#include "util/push_state.hpp"

TERMINAL_TAKE_CARE_OF_WINMAIN

void render_tile_map(const rl::tile_map map, int x = 0, int y = 0) {
	for (int i = 0; i < map.width(); i++) {
		for (int j = 0; j < map.height(); j++) {
			auto &tile = map.get(i, j);
			terminal_put(x + i, y + j, tile.symbol);
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

int main() {
	terminal_open();

	// Printing text
	//terminal_set("window: size=80x60, cellsize=8x8, title='Nechrogue'");

	//terminal_set("jpn font: ./asset/misaki_gothic.ttf, size=8x8, hinting=none");
	//terminal_set("font: ./asset/terminal8x8_gs_ro.png, size=8x8");

	terminal_color("gray");

	terminal_refresh();

	// Wait until user close the window
	while (terminal_read() != TK_CLOSE);

	terminal_close();
}

void test_frame() {
	using namespace rl;

	render_frame(frame(), rect(1, 1, 10, 10));
	render_frame(frame(), rect(3, 3, 10, 10));
	render_frame(frame(), rect(5, 5, 10, 10));
}

void test_tile_map() {
	using namespace rl;

	const tile floor(U'.');

	tile_map map(20, 20);

	tile_map room(10, 5, floor);

	map.set(room, 3, 3);
	map.set(room, 5, 10);

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
