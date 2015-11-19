#include "damage.h"

struct display{
    int width, height;
    SDL_Window *win;
    SDL_Surface *sur;
    SDL_Renderer *ren;
    SDL_Event *e;
};

typedef struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
}button;

display *createDisplay(int width, int height);
void createButtons(button buttonArray[], SDL_Renderer *renderer);
int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos);
int renderButtons(button buttonArray[], int count, SDL_Renderer *renderer, battleState *pState);
void freeButtons(button *buttonArray, int buttons);
void closeDisplay(display *d);

