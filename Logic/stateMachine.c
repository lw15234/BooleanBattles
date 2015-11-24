#include <stdio.h>
#include "stateMachine.h"

void runStateMachine(int playerHealth, int abilities, display *d)
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy newEnemy;
    currentBattle *battle = (currentBattle *)malloc(sizeof(currentBattle));
    enemy* pEnemy = &newEnemy;
    int attack = 0, enemyHealth, result = 0;
    int *pEnemyHealth = &enemyHealth, *pPlayerHealth = &playerHealth;
    button buttonArray[4];


    while(result == 0){
        switch(currentState){
            case START:
                createBattle(d, battle);
                createButtons(buttonArray, abilities + 1, d);
                RenderRefresh(d, battle);
                newEnemy = createEnemy(pState, pEnemyHealth);
                break;
            case PLAYERINPUT:
                attack = renderButtons(buttonArray, abilities + 1, d, pState, battle);
                break;
            case PLAYERACTION:
                damageState(attack, pEnemy, pEnemyHealth, pPlayerHealth, pState);
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
