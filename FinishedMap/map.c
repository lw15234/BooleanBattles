#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"
#include "hero.h"
#include "util.h"

const char REGION_MAP_FILENAME[] = "click_map.bmp";
const char ROAD_MAP_FILENAME[] = "road_map.bmp";
const char BACKGROUND_TEXTURE_FILENAME[] = "background1.jpg";
const char HERO_TEXTURE_FILENAME[] = "hero.png";

SDL_Texture* gBackgroundTexture;
SDL_Surface* gClickableMap;
SDL_Surface* gRoadMap;

Hero gHero;
bool gHeroUp = false, gHeroDown = false, gHeroLeft = false, gHeroRight = false;

bool loadMedia(SDL_Renderer* renderer);
int handleEvents(void);
void updateHero(void);


bool mapInit(SDL_Renderer* renderer) {
    int imgFlags;
    imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		return false;
	}
    if(!loadMedia(renderer)) {
        return false;
    }
    return 1;
}

int mapShow(SDL_Renderer* renderer, int possibleLevelId) {
    int event;
	for(;;) {
        event = handleEvents();
        if(event == EVENT_QUIT) {
            return EVENT_QUIT;
        } else if(event == possibleLevelId) {
            return event;
        }
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, gBackgroundTexture, NULL, NULL);
		updateHero();
		HeroRender(&gHero, renderer);
		SDL_RenderPresent(renderer);
	}
}

void mapCleanup(void) {
    SDL_FreeSurface(gClickableMap);
    SDL_FreeSurface(gRoadMap);
    SDL_DestroyTexture(gBackgroundTexture);
    SDL_DestroyTexture(gHero.texture);
}

bool loadMedia(SDL_Renderer* renderer) {
	Rect heroWorldRect = {320, 240, 100, 100};
	SDL_Rect heroTextureRect = {0, 0, 205, 246};
	SDL_Texture* heroTexture = loadTexture(HERO_TEXTURE_FILENAME, renderer);
	if(heroTexture == NULL) {
		return false;
	}
	HeroInit(&gHero, heroWorldRect, heroTextureRect, heroTexture);
	gBackgroundTexture = loadTexture(BACKGROUND_TEXTURE_FILENAME, renderer);
	if(gBackgroundTexture == NULL) {
		return false;
	}
	gClickableMap = SDL_LoadBMP(REGION_MAP_FILENAME);
	if(gClickableMap == NULL) {
        return false;
	}
	gRoadMap = SDL_LoadBMP(ROAD_MAP_FILENAME);
	if(gRoadMap == NULL) {
        return false;
	}

	return true;
}

int handleEvents(void) {
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT) {
			return EVENT_QUIT;
		}
		if(event.type == SDL_KEYDOWN) {
			switch(event.key.keysym.sym) {
				case SDLK_UP:
					gHeroUp = true;
					gHeroDown = false;
					break;
				case SDLK_DOWN:
					gHeroDown = true;
					gHeroUp = false;
					break;
				case SDLK_LEFT:
					gHeroLeft = true;
					gHeroRight = false;
					break;
				case SDLK_RIGHT:
					gHeroRight = true;
					gHeroLeft = false;
					break;
			}
		} else if (event.type == SDL_KEYUP) {
			switch(event.key.keysym.sym) {
				case SDLK_UP:
					gHeroUp = false;
					break;
				case SDLK_DOWN:
					gHeroDown = false;
					break;
				case SDLK_LEFT:
					gHeroLeft = false;
					break;
				case SDLK_RIGHT:
					gHeroRight = false;
					break;
                case SDLK_RETURN:
                    return getPixel(gClickableMap, (int)gHero.worldRect.x, (int)gHero.worldRect.y);
			}
		}
	}
	return EVENT_NULL;
}

void updateHero(void) {
    int pixel;
    SDL_Rect nextPos;
    if(gHeroUp) {
        nextPos = HeroCalcNewPosition(&gHero, true, false, false, false);
		if(getPixel(gRoadMap, nextPos.x, nextPos.y) == 0) {
		    HeroMoveUp(&gHero);
		}
	}
	if(gHeroDown) {
        nextPos = HeroCalcNewPosition(&gHero, false, true, false, false);
		if(getPixel(gRoadMap, nextPos.x, nextPos.y) == 0) {
            HeroMoveDown(&gHero);
		}
	}
	if(gHeroLeft) {
        nextPos = HeroCalcNewPosition(&gHero, false, false, true, false);
		if(getPixel(gRoadMap, nextPos.x, nextPos.y) == 0) {
            HeroMoveLeft(&gHero);
		}
	}
	if(gHeroRight) {
        nextPos = HeroCalcNewPosition(&gHero, false, false, false, true);
		if(getPixel(gRoadMap, nextPos.x, nextPos.y) == 0) {
            HeroMoveRight(&gHero);
		}
	}
}



