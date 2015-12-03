#include <stdio.h>
#include "play.h"

#define WIDTH 1080
#define HEIGHT 720

typedef enum gameState{
    GAMESTART,
    MAP,
    BATTLE,
    GAMEEND
} gameState;

int main(void)
{
    int playerHealth = 3, currentLevel = -1, game = 1, result;
    gameState currentState = GAMESTART;
    display *d = NULL;

    while(game){
        switch(currentState){
            case GAMESTART:
                d = createDisplay(WIDTH, HEIGHT);
                currentState = MAP;
                break;
            case MAP:
                /*currentLevel = someMapFunction();*/
                currentLevel++;
                if(currentLevel < LEVELS){
                    currentState = BATTLE;
                }
                else{
                    fprintf(stdout, "You win! Game over.\n");
                    currentState = GAMEEND;
                }
                break;
            case BATTLE:
                result = runStateMachine(&playerHealth, currentLevel, d);
                if(result == 1){
                    currentState = MAP;
                }
                else{
                    currentState = GAMEEND;
                }
                break;
            case GAMEEND:
                closeDisplay(d);
                game = 0;
                break;
        }
    }

    return 0;
}
