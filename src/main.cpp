#include "BearLibTerminal.h"

TERMINAL_TAKE_CARE_OF_WINMAIN

int main() {
	terminal_open();

	// Printing text
	terminal_set("window: size=80x60, cellsize=8x8, title='Nechrogue'");

	terminal_set("jpn font: ./asset/misaki_gothic.ttf, size=8x8, hinting=none");
	terminal_set("font: ./asset/terminal8x8_gs_ro.png, size=8x8");

	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			terminal_print(i, j, "#");
		}
	}

	int x = 51;
	int y = 1;

	terminal_print(x, y++, "[font=jpn]つぎはぎアリス[/font]");
	y++;
	terminal_print(x, y++, "Position: [font=jpn]アリス");
	terminal_print(x, y++, "Class: [font=jpn]ステーシー/ロマネスク");
	y++;
	terminal_print(x, y++, "Head:");
	terminal_print(x + 3, y++, "[font=jpn]【のうみそ】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【めだま】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【あご】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【リフレックス】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【アクセサリー】[/font][U+0003]");

	y++;
	terminal_print(x, y++, "Arms:");
	terminal_print(x + 3, y++, "[font=jpn]【こぶし】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【うで】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【かた】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【肉切り包丁】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【合金トランク】[/font]");

	y++;
	terminal_print(x, y++, "Legs:");
	terminal_print(x + 3, y++, "[font=jpn]【ほね】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【ほね】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【あし】[/font]");

	y++;
	terminal_print(x, y++, "Torso:");
	terminal_print(x + 3, y++, "[font=jpn]【せぼね】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【はらわた】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【はらわた】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【つぎはぎ】[/font]");
	terminal_print(x + 3, y++, "[font=jpn]【スチールボーン】[/font]");

	terminal_refresh();

	// Wait until user close the window
	while (terminal_read() != TK_CLOSE);

	terminal_close();
}
