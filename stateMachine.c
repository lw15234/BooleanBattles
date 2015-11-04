#include "stateMachine.h"
#include <stdio.h>

void runStateMachine()
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy newEnemy;
    enemy* pEnemy = &newEnemy;
    int fire, water, grass, enemyHealth, playerHealth, result = 0;
    int *pFire = &fire, *pWater = &water, *pGrass = &grass;
    int *pEnemyHealth = &enemyHealth, *pPlayerHealth = &playerHealth;

    while(result == 0){
        switch(currentState){
            case START:
                playerHealth = 3;
                newEnemy = createEnemy(pState, pEnemyHealth);
                break;
            case PLAYERINPUT:
                playerInput(pFire, pWater, pGrass, pState);
                break;
            case PLAYERACTION:
                damageState(fire, water, grass, pEnemy, pPlayerHealth, pEnemyHealth, pState);
                break;
            case WIN:
                result = 1;
                break;
            case LOSE:
                result = -1;
                break;
        }
    }
}
