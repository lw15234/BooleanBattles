#include "util.h"
#include <SDL2/SDL_image.h>


bool PointInRect(Rect r, float x, float y) {
	return x > r.x && y > r.y && x < r.x + r.w && y < r.y + r.h;
}

SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
	SDL_Texture* newTexture;
	SDL_Surface* loadedSurface;

	loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL) {
		printf("Failed to load: %s\n", path);
		return NULL;
	}
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if(newTexture == NULL) {
		printf("Failed to create texture for: %s\n", path);
		return NULL;
	}
	return newTexture;
}

Uint32 getPixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        } else {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;
    }
}
