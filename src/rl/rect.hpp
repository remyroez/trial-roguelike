
#ifndef RL_RECT_HPP
#define RL_RECT_HPP

namespace rl {

struct rect {
	int x;
	int y;
	int width;
	int height;

	rect(int x, int y, int w, int h) : x(x), y(y), width(w), height(h) {}
	rect() : rect(0, 0, 0, 0) {}
};

}  // namespace rl

#endif // RL_RECT_HPP
