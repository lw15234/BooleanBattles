#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "map.h"


const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 786;


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;


bool Init(void);
void Cleanup(void);


int main(int argc, char** argv)
{
    int i;
	if(!Init()) {
		printf("Initialization failed!\n");
		return 1;
	}
	mapInit(gRenderer);
	for(;;) {
        i = mapShow(gRenderer, 5);
        if(i == EVENT_QUIT) {
            break;
        } else {
            printf("%d\n", i);
        }
	}
	mapCleanup();
	Cleanup();
	return 0;
}

bool Init(void) {
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
	return true;
}

void Cleanup(void) {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}








