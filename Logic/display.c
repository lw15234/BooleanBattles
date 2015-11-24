#include "SDL.h"
#include "display.h"
#include <stdio.h>
#include <math.h>
#define BUTTONS 4

/*A struct to contain our display*/
struct display{
    int width, height;
    SDL_Window *win;
    SDL_Surface *sur;
    SDL_Renderer *ren;
    SDL_Event *e;
};

int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos);


/*Initialise SDL and create a new display struct*/
display *createDisplay(int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        exit(1);
    }
    display *d = (display *)malloc(sizeof(display));
    d->width = width;
    d->height = height;
    d->win = NULL;
    d->ren = NULL;
    d->win = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, d->width, d->height, 0);
    if(d->win == NULL){
        fprintf(stderr, "Window could not be created! SDL_Error: %s.\n", SDL_GetError());
        exit(1);
    }
    d->ren = SDL_CreateRenderer(d->win, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderPresent(d->ren);
    return d;
}

/*Create input buttons for player*/
void createButtons(button buttonArray[], int abilities, display *d)
{
    int w = 100, h = 100, x = 250, y = 550, i;
    FILE* buttonFiles;
    char offFile[30], onFile[30];

    
    // Sets the positions of the buttons 
    buttonFiles = fopen("buttons/buttonFiles.txt", "r");
    for(i = 0; i < abilities; i++){
        buttonArray[i].buttonPos.w = w;
        buttonArray[i].buttonPos.h = h;
        buttonArray[i].buttonPos.y = y;
        if(i == abilities - 1){
            buttonArray[i].buttonPos.x = x + (w + 50) * i;
        }
        else{
            buttonArray[i].buttonPos.x = x + (w + 10) * i;
        }
        // Buttons images are read from a file of files
        if(fscanf(buttonFiles, "%s %s", offFile, onFile) == 2){
            buttonArray[i].buttonSur[0] = SDL_LoadBMP(offFile);
            buttonArray[i].buttonSur[1] = SDL_LoadBMP(onFile);
            buttonArray[i].buttonTex[0] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[0]);
            buttonArray[i].buttonTex[1] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[1]);
        }
        else{
            printf("Could not find files\n");
            exit(1);
        }
    }
    fclose(buttonFiles);
}

/*Checks for the left mouse button being clicked and checks where on the screen
    it was pressed, if over a button it toggles the button's state.*/
int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos)
{
	int x, y;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&x, &y);
		if( x > buttonPos.x && x < buttonPos.x + buttonPos.w &&
            y > buttonPos.y && y < buttonPos.y + buttonPos.h){
			return 1 - choice;
		}
    }
    return choice;
}

/*Display our buttons on screen until Attack button is pressed*/
int renderButtons(button buttonArray[], int count, display *d, battleState *pState)
{
    int i, run = 1, attack = 0;
    int choice[BUTTONS] = {0};
    SDL_Event event;
    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
            }
            for(i = 0; i < count; i++){
                choice[i] = pressButton(&event, choice[i], buttonArray[i].buttonPos);
            }
            if(choice[count - 1] == 1){
                run = 0;
            }
        }
        //Renders the button the the user has selected
        SDL_RenderClear(d->ren);
        for(i = 0; i < count; i++){
            SDL_RenderCopy(d->ren, buttonArray[i].buttonTex[choice[i]], NULL, 
                &buttonArray[i].buttonPos);
        }
        SDL_RenderPresent(d->ren);
    }
    for(i = 0; i < count -1; i++){
        attack += choice[i] * pow(10, i);
    }
    *pState = PLAYERACTION;
    return attack;
}

/*Free memory used by buttons*/
void freeButtons(button *buttonArray, int buttons)
{
    int i, j;    
    for(i = 0; i < buttons; i++){
        for(j = 0; j < 2; j++){
            SDL_DestroyTexture(buttonArray[i].buttonTex[j]);
            SDL_FreeSurface(buttonArray[i].buttonSur[j]);
        }
    }
}

/*Free memory used by display and close*/
void closeDisplay(display *d)
{
    SDL_DestroyWindow(d->win);
    SDL_Quit();
    free(d);
    return;
}




/*Test display module*/
void testDisplay()
{
    display *d = createDisplay(1080, 720);

    button buttonArray[BUTTONS];
    battleState state = PLAYERINPUT;

    createButtons(buttonArray, 4, d);
    renderButtons(buttonArray, 4, d, &state);

    closeDisplay(d);
    succeed("Display module ok");
    return;
}
