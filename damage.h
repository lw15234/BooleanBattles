/*Checks player and enemy are both still alive. Triggers win/lose conditions if not.*/

#include "checkAttack.h"

int damageState(int fire, int water, int grass, enemy* pEnemy, int* enemyHealth, int* playerHealth, battleState* pState);
void implementDamage(int fire, int water, int grass, enemy* pEnemy, int* enemyHealth, int* playerHealth);
int checkHealth(int enemyHealth, int playerHealth, battleState* pState);
int loseBattle();
int winBattle();
int subTestDamage(int grass, int water, int fire, int* pTurns);
