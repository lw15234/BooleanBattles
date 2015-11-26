#include "util.h"


bool PointInRect(Rect r, float x, float y) {
	return x > r.x && y > r.y && x < r.x + r.w && y < r.y + r.h;
}
