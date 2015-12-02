/*Generates information about our enemy/level*/

#include "enemy.h"
#include <string.h>
#include <stdlib.h>

/*Something to fill space in our weakness array. Not an actual attack.*/
#define FILLER -99


void fillWeaknessArray(enemy* newEnemy, int weaknesses[]);
/*void fillWeaknessFiller(enemy* newEnemy);*/


/*Create an enemy structure*/
struct enemy *createEnemy(int level)
{
    enemy enemyArray[LEVELS] = {
        {1, 1, "F",                     {  1,                       FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/uglygreentroll.bmp", "background.bmp", "questions/one.bmp","dialogue/one.bmp" }, 
        {1, 1, "!F",                    {  0,                       FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/faun.bmp", "background.bmp", "questions/two.bmp", "dialogue/two.bmp" },
        {1, 1, "!!F",                   {  1,                       FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/goblin.bmp", "background.bmp", "questions/three.bmp", "dialogue/three.bmp" },
        {2, 1, "F && I",                { 11,                       FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/fox.bmp", "background.bmp", "questions/four.bmp", "dialogue/four.bmp" },
        {2, 3, "F || I",                {  1,  10,  11,                             FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/werewolf.bmp", "background.bmp", "questions/five.bmp", "dialogue/five.bmp" },
        {2, 3, "F || !I",               {  0,   1,  10,                             FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/vampire.bmp", "background.bmp", "questions/six.bmp", "dialogue/six.bmp" },
        {2, 3, "!(F && I)",             {  0,   1,  10,                             FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/ninja.bmp", "background.bmp", "questions/seven.bmp","dialogue/seven.bmp" },
        {3, 1, "F && I && L",           {111,                       FILLER, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/alien.bmp", "background.bmp", "questions/eight.bmp", "dialogue/eight.bmp" },
        {3, 3, "(F || I) && L",         {101, 110, 111,                             FILLER, FILLER, FILLER, FILLER, FILLER} , "enemies/oneeyedmonster.bmp", "background.bmp", "questions/nine.bmp", "dialogue/nine.bmp" },
        {3, 4, "(F && I) || (!I && L)", { 11, 100, 101, 111,                                FILLER, FILLER, FILLER, FILLER} , "enemies/weirdguy.bmp", "background.bmp", "questions/ten.bmp", "dialogue/ten.bmp" },
    };

    enemy *newEnemy = malloc(sizeof(enemy));
    newEnemy->abilities = enemyArray[level].abilities;
    newEnemy->health = enemyArray[level].health;
    strcpy(newEnemy->equation, enemyArray[level].equation);
    strcpy(newEnemy->enemySprite, enemyArray[level].enemySprite);
    strcpy(newEnemy->background, enemyArray[level].background);
    strcpy(newEnemy->question, enemyArray[level].question);
<<<<<<< HEAD
	strcpy(newEnemy->dialogue, enemyArray[level].dialogue);
=======
	 strcpy(newEnemy->dialogue, enemyArray[level].dialogue);
>>>>>>> c210c393b7facccf28cd0fcf5d6d27cbde6fda52
    fillWeaknessArray(newEnemy, enemyArray[level].weakness);
    return newEnemy;
}

/*Fill an enemy's weakness array*/
void fillWeaknessArray(enemy* newEnemy, int weaknesses[])
{
    int i;
    for(i = 0; i < ATTACKCOMBOS; i++){
        newEnemy->weakness[i] = weaknesses[i];
    }
    return;
}

/*Fill any space in the weakness array with filler. No longer needed.*/
/*
void fillWeaknessFiller(enemy* newEnemy)
{
    int i;
    for(i = newEnemy->health; i < ATTACKCOMBOS; i++){
        newEnemy->weakness[i] = FILLER;
    }
    return;
}*/

/*Test the enemy module*/
void testEnemy()
{
    int i;
    enemy *newEnemy = createEnemy(8);

    if(newEnemy->weakness[0] != 101){
        fail("Weakness 0 set incorrectly");
    }
    if(newEnemy->weakness[1] != 110){
        fail("Weakness 1 set incorrectly");
    }
    if(newEnemy->weakness[2] != 111){
        fail("Weakness 2 set incorrectly");
    }
    if(newEnemy->health != 3){
        fail("Health set incorrectly");
    }
    if(strcmp(newEnemy->equation, "(F || I) && L") != 0){
        fail("Equation set incorrectly");
    }
    if(newEnemy->abilities != 3){
        fail("Abilities set incorrectly");
    }
    for(i = newEnemy->health; i < ATTACKCOMBOS; i++){
        if(newEnemy->weakness[i] != FILLER){
            fail("Filler weakness not set");
        }
    }
    free(newEnemy);
    succeed("Enemy module ok");
}


