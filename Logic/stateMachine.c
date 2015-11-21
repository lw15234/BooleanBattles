#include <stdio.h>
#include "stateMachine.h"

void runStateMachine(int playerHealth, int abilities, display *d)
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy newEnemy;
    enemy* pEnemy = &newEnemy;
    int attack = 0, enemyHealth, result = 0;
    int *pEnemyHealth = &enemyHealth, *pPlayerHealth = &playerHealth;
    button buttonArray[3];

    while(result == 0){
        switch(currentState){
            case START:
                createButtons(buttonArray, abilities + 1, d);
                newEnemy = createEnemy(pState, pEnemyHealth);
                break;
            case PLAYERINPUT:
                attack = renderButtons(buttonArray, abilities + 1, d, pState);
printf("%d\n", attack);
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
