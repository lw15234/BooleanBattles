/*Generates information about our enemy/level*/

#include "base.h"

/*The total number of possible attacks*/
#define ATTACKCOMBOS 8

/*Contains information for our enemy/level*/
typedef struct enemy{
    int abilities;
    int health;
    char equation[30];
    int weakness[ATTACKCOMBOS];
}enemy;

/*Create an enemy structure*/
struct enemy *createEnemy(battleState* pState, int level);
