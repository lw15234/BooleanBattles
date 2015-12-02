#include <stdio.h>
#include <stdlib.h>
#include "stateMachine.h"

int runStateMachine(int *playerHealth, int currentLevel, display *d)
{
    battleState currentState = START;
    battleState* pState = &currentState;
    enemy *newEnemy = NULL;
    currentBattle *battle = NULL;
    int attack = 0, result = 0, abilities = 0, success;
    button *buttonArray = NULL;
    int used[ATTACKCOMBOS] = {FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER};

    while(result == 0){
        switch(currentState){
            case START:
                newEnemy = createEnemy(currentLevel);
		battle = createBattle(d, newEnemy);
                printf("Current health: %d\n", *playerHealth);
                printf("%s\n", newEnemy->equation);
                abilities = newEnemy->abilities;
                buttonArray = createButtons(abilities, d);
                RenderRefresh(d, battle);
                RenderPresent(d);
                currentState = PLAYERINPUT;
                break;
            case PLAYERINPUT:
                attack = renderButtons(buttonArray, abilities, used, d, pState, battle);
                //This allows the user to close the game
                if(attack == -1){
                    return -2;
                }
                break;
            case PLAYERACTION:
                success = checkAttack(attack, newEnemy);
                displayAttack(attack, d, success);
                damageState(success, newEnemy, playerHealth, pState);
                break;
            case WIN:
                result = 1;
                break;
            case LOSE:
                result = -1;
                break;
        }
    }

    freeBattle(buttonArray, abilities + 1, battle);
    free(battle);
    free(newEnemy);
    return result;
}
