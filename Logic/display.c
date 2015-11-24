#include "SDL.h"
#include "display.h"
#include <stdio.h>
#include <math.h>
#define BUTTONS 4

struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
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
button *createButtons(int abilities, display *d)
{
    int w = 100, h = 100, x = 250, y = 550, i;
    FILE* buttonFiles;
    char offFile[30], onFile[30];
    button *buttonArray = malloc((abilities + 1) * sizeof(button));

    
    // Sets the positions of the buttons 
    buttonFiles = fopen("buttons/buttonFiles.txt", "r");
    for(i = 0; i < abilities + 1; i++){
        buttonArray[i].buttonPos.w = w;
        buttonArray[i].buttonPos.h = h;
        buttonArray[i].buttonPos.y = y;
        if(i == abilities){
            buttonArray[i].buttonPos.x = x + (w + 50) * 3;
            buttonArray[i].buttonSur[0] = SDL_LoadBMP("buttons/offAttack.bmp");
            buttonArray[i].buttonSur[1] = SDL_LoadBMP("buttons/onAttack.bmp");
            buttonArray[i].buttonTex[0] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[0]);
            buttonArray[i].buttonTex[1] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[1]);
        }
        else{
            buttonArray[i].buttonPos.x = x + (w + 10) * i;
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
        // Buttons images are read from a file of files
        
    }
    fclose(buttonFiles);
    return buttonArray;
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
int renderButtons(button buttonArray[], int abilities, display *d, battleState *pState, currentBattle *battle)
{
    int i, run = 1, attack = 0;
    int choice[BUTTONS] = {0};
    SDL_Event event;
    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
            }
            for(i = 0; i < abilities + 1; i++){
                choice[i] = pressButton(&event, choice[i], buttonArray[i].buttonPos);
            }
            if(choice[abilities] == 1){
                run = 0;
            }
        }
        //Renders the button the the user has selected
        RenderRefresh(d, battle);
        for(i = 0; i < abilities + 1; i++){
            SDL_RenderCopy(d->ren, buttonArray[i].buttonTex[choice[i]], NULL, 
                &buttonArray[i].buttonPos);
        }
        SDL_RenderPresent(d->ren);
    }
    for(i = 0; i < abilities; i++){
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
    free(buttonArray);
}

/*Free memory used by display and close*/
void closeDisplay(display *d)
{
    SDL_DestroyWindow(d->win);
    SDL_Quit();
    free(d);
    return;
}

entity *createEntity(char *filename, int x, int y, int w, int h, display *d)
{
	entity *ent = (entity*)malloc(sizeof(entity));
	ent->entityPos.x = x;
	ent->entityPos.y = y;
	ent->entityPos.w = w;
	ent->entityPos.h = h;
	ent->entitySur = SDL_LoadBMP(filename);
	ent->entityTex = SDL_CreateTextureFromSurface(d->ren, ent->entitySur);
	return ent;
}
/*Can use the level in this function to choose the background and the enemy*/
void createBattle(display *d, currentBattle *battle)
{
	
	battle->sur = SDL_LoadBMP("background.bmp");
	battle->tex = SDL_CreateTextureFromSurface(d->ren, battle->sur);
	
	battle->hero = createEntity("hero.bmp", 100, 100, 100, 100, d);
	battle->enemy = createEntity("hero.bmp", 500, 100, 100, 100, d);
}

void RenderRefresh(display *d, currentBattle *battle)
{
    SDL_RenderClear(d->ren);
    SDL_RenderCopy(d->ren, battle->tex, NULL, NULL);
    SDL_RenderCopy(d->ren, battle->hero->entityTex, NULL, &battle->hero->entityPos);
    SDL_RenderCopy(d->ren, battle->enemy->entityTex, NULL, &battle->enemy->entityPos);
}

/*Test display module*/
void testDisplay()
{
    currentBattle *battle = (currentBattle *)malloc(sizeof(currentBattle));
    display *d = createDisplay(1080, 720);

    button *buttonArray;
    battleState state = PLAYERINPUT;

    buttonArray = createButtons(3, d);
    renderButtons(buttonArray, 3, d, &state, battle);

    closeDisplay(d);
    succeed("Display module ok");
    return;
}
