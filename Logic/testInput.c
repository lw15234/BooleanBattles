#include "testInput.h"
#include <stdio.h>

int playerInput(battleState *pState)
{
    int attack, fire, water, grass;
    scanf("%d %d %d", &fire, &water, &grass);
    *pState = PLAYERACTION;
    attack = grass * 100 + water * 10 + fire;
    return attack;
}

void testInput()
{
    succeed("Input ok");
}
