/*Implements damage and checks if the battle is over*/

#include "damage.h"
#include <stdio.h>


void implementDamage(int attack, enemy* pEnemy, int* enemyHealth, int* playerHealth);
int checkHealth(int enemyHealth, int playerHealth, battleState* pState);
int loseBattle();
int winBattle();
int subTestDamage(int attack, int* pTurns);


/*Runs functions for the damage state in state machine*/
int damageState(int attack, enemy* pEnemy, int* enemyHealth, int* playerHealth, battleState* pState)
{
    implementDamage(attack, pEnemy, enemyHealth, playerHealth);
    return checkHealth(*enemyHealth, *playerHealth, pState);
}

/*Checks if an attack was successful and damages player or enemy accordingly*/
void implementDamage(int attack, enemy* pEnemy, int* enemyHealth, int* playerHealth)
{
    if(checkAttack(attack, pEnemy)){
        (*enemyHealth)--;
    }
    else{
        (*playerHealth)--;
    }
    return;
}

/*Checks if the player and enemy are still alive*/
int checkHealth(int enemyHealth, int playerHealth, battleState* pState)
{
    if(playerHealth <= 0){
        *pState = LOSE;
        return loseBattle();
    }
    else if(enemyHealth <= 0){
        *pState = WIN;
        return winBattle();
    }
    *pState = PLAYERINPUT;
    return 0;
}

/*The player has lost the battle*/
int loseBattle()
{
    printf("You lose. Sorry :(\n");
    return -1;
}

/*The player has won the battle*/
int winBattle()
{
    printf("You win! Congratz!\n");
    return 1;
}

/*Test the damage module*/
void testDamage()
{
    int i, j, k, l = 0, turns = 0;
    int *pTurns = &turns;
    int results[ATTACKCOMBOS][2];
    for(i = 0; i <= 1; i++){
        for(j = 0; j <= 1; j++){
            for(k = 0; k <= 1; k++){
                turns = 0;
                results[l][0] = subTestDamage(i * 100 + j * 10 + k, pTurns);
                results[l][1] = turns;
                l++;
            }
        }
    }
    for(l = 0; l < 5; l++){
        if(results[l][0] != -1){
            fail("Lose check failed.");
        }
    }
    for(l = 5; l < ATTACKCOMBOS; l++){
        if(results[l][0] != 1){
            fail("Win check failed.");
        }
    }
    for(l = 0; l < ATTACKCOMBOS; l++){
        if(results[l][1] != 3){
            fail("Turn counter failed.");
        }
    }
    succeed("Damage ok");

}

/*Part of the test function*/
int subTestDamage(int attack, int* pTurns)
{
    int playerHealth = 3, enemyHealth = 3, result = 0;
    int *pPlayerHealth = &playerHealth, *pEnemyHealth = &enemyHealth;
    battleState currentState;
    battleState* pState = &currentState;
    enemy newEnemy = createEnemy(pState, pEnemyHealth);
    enemy* pEnemy = &newEnemy;
    while(result == 0){
        result = damageState(attack, pEnemy, pEnemyHealth, pPlayerHealth, pState);
        (*pTurns)++;
    }
    return result;
}
