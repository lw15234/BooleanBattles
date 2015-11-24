#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include <stdbool.h>

typedef struct Rect Rect;
struct Rect {
	float x, y, w, h;
};

bool PointInRect(Rect r, float x, float y);

#endif
