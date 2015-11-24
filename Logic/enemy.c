/*Generates information about our enemy/level*/

#include "enemy.h"
#include <string.h>
#include <stdlib.h>


void fillWeaknessArray(enemy* pEnemy, int weaknesses[]);
void fillWeaknessFiller(enemy* pEnemy);


/*Create an enemy structure*/
struct enemy *createEnemy(battleState* pState, int* pEnemyHealth)
{
    enemy *newEnemy = malloc(sizeof(enemy));
    int tmp[] = {101, 110, 111};
    newEnemy->solutions = sizeof(tmp) / sizeof(tmp[0]);
    newEnemy->equation = "(F || W) && G";
    fillWeaknessArray(newEnemy, tmp);
    fillWeaknessFiller(newEnemy);
    *pEnemyHealth = newEnemy->solutions;
    *pState = PLAYERINPUT;
    return newEnemy;
}

/*Fill an enemy's weakness array*/
void fillWeaknessArray(enemy* pEnemy, int weaknesses[])
{
    int i;
    for(i = 0; i < (*pEnemy).solutions; i++){
        (*pEnemy).weakness[i] = weaknesses[i];
    }
    return;
}

/*Fill any space in the weakness array with filler*/
void fillWeaknessFiller(enemy* pEnemy)
{
    int i;
    for(i = (*pEnemy).solutions; i < ATTACKCOMBOS; i++){
        (*pEnemy).weakness[i] = FILLER;
    }
    return;
}

/*Test the enemy module*/
void testEnemy()
{
    int i;
    enemy *newEnemy;
    battleState currentState;
    battleState* pState = &currentState;
    int enemyHealth;
    int* pEnemyHealth = &enemyHealth;
    newEnemy = createEnemy(pState, pEnemyHealth);
    if(newEnemy->weakness[0] != 101){
        fail("Weakness 0 set incorrectly");
    }
    if(newEnemy->weakness[1] != 110){
        fail("Weakness 1 set incorrectly");
    }
    if(newEnemy->weakness[2] != 111){
        fail("Weakness 2 set incorrectly");
    }
    if(newEnemy->solutions != 3){
        fail("Solutions set incorrectly");
    }
    if(strcmp(newEnemy->equation, "(F || W) && G") != 0){
        fail("Equation set incorrectly");
    }
    for(i = newEnemy->solutions; i < ATTACKCOMBOS; i++){
        if(newEnemy->weakness[i] != FILLER){
            fail("Filler weakness not set");
        }
    }
    if(*pEnemyHealth != 3){
        fail("Enemy health not set");
    }
    if(*pState != PLAYERINPUT){
        fail("State not set");
    }
    free(newEnemy);
    succeed("Enemy module ok");
}


