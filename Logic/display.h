#include "damage.h"
#include "SDL.h"

typedef struct display display;
typedef struct button button;
typedef struct currentBattle currentBattle;
typedef struct entity entity;


struct currentBattle{
    entity *hero; 
    entity *enemy;
    SDL_Surface *sur;
    SDL_Texture *tex;
};



display *createDisplay(int width, int height);
button *createButtons(int abilities, display *d);
int renderButtons(button *buttonArray, int abilities, display *d, battleState *pState, currentBattle *battle);
void freeButtons(button *buttonArray, int buttons);
void closeDisplay(display *d);
entity *createEntity(char *filename, int x, int y, int w, int h, display *d);
void createBattle(display *d, currentBattle *battle);
void RenderRefresh(display *d, currentBattle *battle);
void RenderPresent(display *d);
