/*Generates information about our enemy/level*/

#include "base.h"

/*The total number of possible attacks*/
#define ATTACKCOMBOS 8
/*Something to fill space in our weakness array. Not an actual attack.*/
#define FILLER -99

/*Contains information for our enemy/level*/
typedef struct enemy{
    int weakness[ATTACKCOMBOS];
    int solutions;
    char* equation;
}enemy;

/*Create an enemy structure*/
struct enemy createEnemy(battleState* pState, int* pEnemyHealth);
