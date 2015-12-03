#include "entity.h"

button *createButtons(int abilities, display *d);
int renderButtons(button *buttonArray, int abilities, int used[], display *d, battleState *pState, currentBattle *battle);
int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos);
void freeButtons(button *buttonArray, int buttons);
