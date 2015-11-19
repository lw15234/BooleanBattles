#include "stateMachine.h"
#include "SDL.h"
#include <stdio.h>

void runStateMachine(int playerHealth, int abilities, display *d)
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy newEnemy;
    enemy* pEnemy = &newEnemy;
    int attack = 0, enemyHealth, result = 0;
    int *pEnemyHealth = &enemyHealth, *pPlayerHealth = &playerHealth;
    button *buttonArray = NULL;

    while(result == 0){
        switch(currentState){
            case START:
                createButtons(buttonArray, abilities + 1, d->ren);
                newEnemy = createEnemy(pState, pEnemyHealth);
                break;
            case PLAYERINPUT:
                attack = playerInput(pState);
                break;
            case PLAYERACTION:
                damageState(attack, pEnemy, pPlayerHealth, pEnemyHealth, pState);
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

    return;
}
