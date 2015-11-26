#include <stdio.h>
#include <stdbool.h>
#include "SDL2/include/SDL.h"
#include "SDL2/include/SDL_image.h"
#include "hero.h"
#include "region.h"
#include <Windows.h>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 786;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gBackgroundTexture;
Hero gHero;
bool gHeroUp = false, gHeroDown = false, gHeroLeft = false, gHeroRight = false;
RegionContainer*gRegionContainer;

bool Init(void);
void Cleanup(void);
SDL_Texture* loadTexture(char* path, SDL_Renderer* renderer);
bool loadMedia(void);
bool handleEvents(void);
void updateHero(void);
void initRegions(void);
void rayodehClickHandler(void* data);

int main(int argc, char** argv)
{
	if(!Init()) {
		printf("Initialization failed!\n");
		return 1;
	}
	for(;;) {
		if(!handleEvents()) {
			break;
		}
		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);
		updateHero();
		HeroRender(&gHero, gRenderer);
		SDL_RenderPresent(gRenderer);
	}
	Cleanup();
	return 0;
}

bool Init(void) {
	int imgFlags;
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}
	gWindow = SDL_CreateWindow(
			"Title",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
			);
	if(gWindow == NULL) {
		return false;
	}
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if(gRenderer == NULL) {

		return false;
	}

	imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags)) {
		return false;
	}

	if(!loadMedia()) {
		return false;
	}

	initRegions();

	return true;
}

void Cleanup(void) {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

SDL_Texture* loadTexture(char* path, SDL_Renderer* renderer) {
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

bool loadMedia(void) {
	Rect heroWorldRect = {320, 240, 100, 100};
	SDL_Rect heroTextureRect = {0, 0, 205, 246};
	SDL_Texture* heroTexture = loadTexture("hero.png", gRenderer);
	if(heroTexture == NULL) {
		return false;
	}
	HeroInit(&gHero, heroWorldRect, heroTextureRect, heroTexture);
	gBackgroundTexture = loadTexture("background.bmp", gRenderer);
	if(gBackgroundTexture == NULL) {
		return false;
	}
	return true;
}

bool handleEvents(void) {
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT) {
			return false;
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
			}
		} else if(event.type == SDL_MOUSEBUTTONUP) {
			RegionContainerPassAction(gRegionContainer, ACTION_CLICK, event.button.x, event.button.y);
		}
	}
	return true;
}

void updateHero(void) {
	if(gHeroUp) {
		HeroMoveUp(&gHero);
	}
	if(gHeroDown) {
		HeroMoveDown(&gHero);
	}
	if(gHeroLeft) {
		HeroMoveLeft(&gHero);
	}
	if(gHeroRight) {
		HeroMoveRight(&gHero);
	}
}

void initRegions(void) {
	Rect rayodeh = {730, 50, 200, 90};
	Region* r;
	r = RegionNew(rayodeh);
	RegionAddActionHandler(r, ActionHandlerNew(ACTION_CLICK, rayodehClickHandler, NULL));
	gRegionContainer = RegionContainerNew();
	RegionContainerAddRegion(gRegionContainer, r);
}

void rayodehClickHandler(void* data) {
	MessageBox(0, "Rayodeh clicked", "Click", 0);
}
