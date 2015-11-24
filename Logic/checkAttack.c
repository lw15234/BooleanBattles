/*Checks if enemy is weak to an attack*/

#include "checkAttack.h"

/*Is passed an integer representing an attack combo.
	Checks if integer is in enemy weakness array*/
int checkAttack(int attack, enemy* pEnemy)
{
    int i;
    for (i = 0; i < ATTACKCOMBOS; i++){
        if(attack == pEnemy->weakness[i]){
            return 1;
        }
    }
    return 0;
}


/*Test the check attack module*/
void testCheckAttack()
{
    int i, j, k, l, attack;
    int results[ATTACKCOMBOS];
    battleState currentState;
    battleState* pState = &currentState;
    int enemyHealth;
    int* pEnemyHealth = &enemyHealth;
    enemy *newEnemy = createEnemy(pState, pEnemyHealth);
    l = 0;

    for(i = 0; i <= 1; i++){
        for(j = 0; j <= 1; j++){
            for(k = 0; k <= 1; k++){
                attack = 100* i + 10 * j + k;
                results[l] = checkAttack(attack, newEnemy);
                l++;
            }
        }
    }
    for(l = 0; l < 5; l++){
        if(results[l] != 0){
            fail("Incorrect attack check failed.");
        }
    }
    for(l = 5; l < ATTACKCOMBOS; l++){
        if(results[l] != 1){
            fail("Correct attack check failed.");
        }
    }
    succeed("CheckAttack ok");
}
