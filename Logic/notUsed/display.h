#include "attackAnimation.h"

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
button *createButtons(int abilities, display *d);
int renderButtons(button* buttonArray, int abilities, int used[], display *d, battleState *pState, currentBattle *battle);
void freeBattle(button *buttonArray, int buttons, currentBattle *battle);
void closeDisplay(display *d);
entity *createEntity(char *filename, int x, int y, int w, int h, display *d);
currentBattle *createBattle(display *d, enemy *e);
void RenderRefresh(display *d, currentBattle *battle);
void RenderPresent(display *d);
void displayAttack(int attack, display *d, int success);
