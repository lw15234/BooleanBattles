#include "SDL.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
}
