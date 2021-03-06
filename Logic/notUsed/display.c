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

struct entity{
    SDL_Rect entityPos;
    SDL_Texture *entityTex;
    SDL_Surface *entitySur;
};

struct currentBattle{
    entity *hero; 
    entity *enemy;
	 entity *question;
    entity *dialogue;
    SDL_Surface *sur;
    SDL_Texture *tex;
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
    button *buttonArray = (button *)malloc((abilities + 1) * sizeof(button));

    
    // Sets the positions of the buttons 
    buttonFiles = fopen("buttons/buttonFiles.txt", "r");
    for(i = 0; i < abilities + 1; i++){
        buttonArray[i].buttonPos.w = w;
        buttonArray[i].buttonPos.h = h;
        buttonArray[i].buttonPos.y = y;
        if(i == abilities){
            buttonArray[i].buttonPos.x = x + (w + 50) * 3;
            buttonArray[i].buttonSur[0] = SDL_LoadBMP("buttons/offAttack.bmp");
			SDL_SetColorKey( buttonArray[i].buttonSur[0], SDL_TRUE, SDL_MapRGB(buttonArray[i].buttonSur[0]->format, 228, 129, 250 ));
            buttonArray[i].buttonSur[1] = SDL_LoadBMP("buttons/onAttack.bmp");
			SDL_SetColorKey( buttonArray[i].buttonSur[1], SDL_TRUE, SDL_MapRGB(buttonArray[i].buttonSur[1]->format, 228, 129, 250 ));
            buttonArray[i].buttonTex[0] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[0]);
            buttonArray[i].buttonTex[1] = 
                SDL_CreateTextureFromSurface(d->ren, buttonArray[i].buttonSur[1]);
        }
        else{
            buttonArray[i].buttonPos.x = x + (w + 10) * i;
            if(fscanf(buttonFiles, "%s %s", offFile, onFile) == 2){
                buttonArray[i].buttonSur[0] = SDL_LoadBMP(offFile);
				SDL_SetColorKey( buttonArray[i].buttonSur[0], SDL_TRUE, SDL_MapRGB(buttonArray[i].buttonSur[0]->format, 228, 129, 250 ));
                buttonArray[i].buttonSur[1] = SDL_LoadBMP(onFile);
				SDL_SetColorKey( buttonArray[i].buttonSur[1], SDL_TRUE, SDL_MapRGB(buttonArray[i].buttonSur[1]->format, 228, 129, 250 ));
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
int renderButtons(button buttonArray[], int abilities, int used[], display *d, battleState *pState, currentBattle *battle)
{
    int i, run = 1, attack = 0;
    int choice[BUTTONS] = {0};
    SDL_Event event;
    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
				return -1;
            }
            for(i = 0; i < abilities + 1; i++){
                choice[i] = pressButton(&event, choice[i], buttonArray[i].buttonPos);
            }
            if(choice[abilities] == 1){
                for(i = 0; i < abilities; i++){
                    attack += choice[i] * pow(10, i);
                }
                if(checkUsed(attack, used)){
                    run = 0;
                }
                else{
                    attack = 0;
                    choice[abilities] = 0;
                }
            }
        }
        //Renders the button the user has selected
        RenderRefresh(d, battle);
        for(i = 0; i < abilities + 1; i++){
            SDL_RenderCopy(d->ren, buttonArray[i].buttonTex[choice[i]], NULL, 
                &buttonArray[i].buttonPos);
        }
        SDL_RenderPresent(d->ren);
    }
    *pState = PLAYERACTION;
    return attack;
}

/*Free memory used by buttons*/
void freeBattle(button *buttonArray, int buttons, currentBattle *battle)
{
    int i, j;    
    for(i = 0; i < buttons; i++){
        for(j = 0; j < 2; j++){
            SDL_DestroyTexture(buttonArray[i].buttonTex[j]);
            SDL_FreeSurface(buttonArray[i].buttonSur[j]);
        }
    }
    SDL_DestroyTexture(battle->hero->entityTex);
    SDL_DestroyTexture(battle->enemy->entityTex);
    SDL_DestroyTexture(battle->tex);
    SDL_FreeSurface(battle->hero->entitySur);
    SDL_FreeSurface(battle->enemy->entitySur);
    SDL_FreeSurface(battle->sur);
    
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
	 SDL_SetColorKey( ent->entitySur, SDL_TRUE, SDL_MapRGB(ent->entitySur->format, 228, 129, 250 ));
    ent->entityTex = SDL_CreateTextureFromSurface(d->ren, ent->entitySur);
    return ent;
}

/*Can use the level in this function to choose the background and the enemy*/
currentBattle *createBattle(display *d, enemy *e)
{
    currentBattle *battle = (currentBattle *)malloc(sizeof(currentBattle));

    battle->sur = SDL_LoadBMP(e->background);
    battle->tex = SDL_CreateTextureFromSurface(d->ren, battle->sur);
    battle->hero = createEntity("enemies/hero.bmp", 50, 350, 200, 300, d);
    battle->enemy = createEntity(e->enemySprite, 750, 150, 350, 500, d);
	 battle->question = createEntity(e->question, 300, 50, 500, 75, d);
	 battle->dialogue = createEntity(e->dialogue, 500, 200, 300, 500, d);  

    return battle;
}

void RenderRefresh(display *d, currentBattle *battle)
{
    SDL_RenderClear(d->ren);
    SDL_RenderCopy(d->ren, battle->tex, NULL, NULL);
	 SDL_RenderCopy(d->ren, battle->question->entityTex, NULL, &battle->question->entityPos);
	 SDL_RenderCopy(d->ren, battle->dialogue->entityTex, NULL, &battle->dialogue->entityPos);
	 SDL_Delay(5000);
    SDL_RenderCopy(d->ren, battle->hero->entityTex, NULL, &battle->hero->entityPos);
    SDL_RenderCopy(d->ren, battle->enemy->entityTex, NULL, &battle->enemy->entityPos);
}

void displayAttack(int attack, display *d, int success)
{
    attackManager(attack, d->ren, success);
}

/*Test display module*/
void testDisplay()
{
    display *d = createDisplay(1080, 720);
    enemy *e = createEnemy(8);
    currentBattle *battle = createBattle(d, e);
    int attack, used[ATTACKCOMBOS] = {FILLER};

    button *buttonArray;
    battleState state = PLAYERINPUT;

    used[0] = 1;

    buttonArray = createButtons(3, d);
    attack = renderButtons(buttonArray, 3, used, d, &state, battle);
    displayAttack(attack, d, 1);
    displayAttack(attack, d, 0);
    closeDisplay(d);
    succeed("Display module ok");
    return;
}
