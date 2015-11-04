#include "checkAttack.h"

int checkAttack(int attack, enemy* pEnemy)
{
    int i;
	for (i = 0; i < ATTACKCOMBOS; i++){
        if(attack == (*pEnemy).weakness[i]){
            return 1;
        }
    }
    return 0;
}

void testCheckAttack()
{
    int i, j, k, l, attack;
    int results[ATTACKCOMBOS];
    battleState currentState;
    battleState* pState = &currentState;
    int enemyHealth;
    int* pEnemyHealth = &enemyHealth;
    enemy newEnemy = createEnemy(pState, pEnemyHealth);
    enemy* pEnemy = &newEnemy;
    l = 0;

    for(i = 0; i <= 1; i++){
        for(j = 0; j <= 1; j++){
            for(k = 0; k <= 1; k++){
                attack = 100* i + 10 * j + k;
                results[l] = checkAttack(attack, pEnemy);
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
