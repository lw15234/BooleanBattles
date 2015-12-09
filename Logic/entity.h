#include "baseDisplay.h"



currentBattle *createBattle(display *d, enemy *e);
void RenderRefresh(display *d, currentBattle *battle);
void freeBattle(currentBattle *battle);
int RenderDialogue(display *d, currentBattle *battle);
