#include "input.h"
#include <stdio.h>

void playerInput(int *fire, int *water, int *grass, battleState *pState)
{
    scanf("%d %d %d", fire, water, grass);
    *pState = PLAYERACTION;
    return;
}
