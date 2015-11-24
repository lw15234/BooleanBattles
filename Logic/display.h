#include "damage.h"
#include "SDL.h"

typedef struct display display;
typedef struct button button;

struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
};


display *createDisplay(int width, int height);
void createButtons(button *buttonArray, int abilities, display *d);
int renderButtons(button *buttonArray, int count, display *d, battleState *pState);
void freeButtons(button *buttonArray, int buttons);
void closeDisplay(display *d);
