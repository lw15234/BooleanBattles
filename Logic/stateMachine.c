#include <stdio.h>
#include "stateMachine.h"

void runStateMachine(int *playerHealth, int abilities, display *d)
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy *newEnemy = NULL;
    currentBattle *battle = (currentBattle *)malloc(sizeof(currentBattle));
    int attack = 0, result = 0;
    button *buttonArray = NULL;


    while(result == 0){
        switch(currentState){
            case START:
                createBattle(d, battle);
                buttonArray = createButtons(abilities, d);
                RenderRefresh(d, battle);
                SDL_RenderPresent(d->ren);
                newEnemy = createEnemy(pState, 8);
                break;
            case PLAYERINPUT:
                attack = renderButtons(buttonArray, abilities, d, pState, battle);
                break;
            case PLAYERACTION:
                damageState(attack, newEnemy, playerHealth, pState);
                break;
            case WIN:
                result = 1;
                break;
            case LOSE:
                result = -1;
                break;
        }
    }
    freeButtons(buttonArray, abilities + 1);
    free(newEnemy);
    return;
}
