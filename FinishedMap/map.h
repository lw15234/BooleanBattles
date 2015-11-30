#ifndef _MAP_H_INCLUDED

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define EVENT_NULL 0xffffff
#define EVENT_QUIT 0

int mapShow(SDL_Renderer* renderer, int possibleLevelId);
bool mapInit(SDL_Renderer* renderer);
void mapCleanup(void);

#endif
