#include <stdio.h>
#include "play.h"
#include "SDL.h"

#define WIDTH 1080
#define HEIGHT 720
#define ABILITIES 3

int main(void)
{
    int playerHealth = 3;

    display *d = createDisplay(WIDTH, HEIGHT);
    runStateMachine(&playerHealth, ABILITIES, d);
    closeDisplay(d);

    return 0;
}
