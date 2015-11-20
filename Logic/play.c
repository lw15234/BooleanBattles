#include <stdio.h>
#include "play.h"
#include "SDL.h"

#define WIDTH 1080
#define HEIGHT 720
#define PLAYERHEALTH 3
#define ABILITIES 3

int main(void)
{
    display *d = createDisplay(WIDTH, HEIGHT);
    runStateMachine(PLAYERHEALTH, ABILITIES, d);
    closeDisplay(d);

    return 0;
}
