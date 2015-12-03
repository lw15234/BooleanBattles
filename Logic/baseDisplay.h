#include "damage.h"
#include "SDL.h"

#define WINDOWWIDTH 1080
#define WINDOWHEIGHT 720

typedef struct display display;
typedef struct button button;
typedef struct currentBattle currentBattle;
typedef struct entity entity;

struct display{
    int width, height;
    SDL_Window *win;
    SDL_Surface *sur;
    SDL_Renderer *ren;
    SDL_Event *e;
};

display *createDisplay(int width, int height);
void closeDisplay(display *d);
