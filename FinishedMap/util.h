#ifndef _UTIL_H_INCLUDED
#define _UTIL_H_INCLUDED

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct Rect Rect;
struct Rect {
	float x, y, w, h;
};

bool PointInRect(Rect r, float x, float y);
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);
Uint32 getPixel(SDL_Surface *surface, int x, int y);

#endif
