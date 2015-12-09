#include "displayButtons.h"

struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
};

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
                fprintf(stderr, "Could not find files\n");
                exit(1);
            }
        }
        // Buttons images are read from a file of files
        
    }
    fclose(buttonFiles);
    return buttonArray;
}

int renderButtons(button *buttonArray, int abilities, int used[], display *d, battleState *pState, currentBattle *battle)
{
    int i, run = 1, attack = 0;
    SDL_Event event;
    int *choice = calloc(abilities + 1, sizeof(int));
    if(choice == NULL){
        fprintf(stderr, "Could not free space for choice array\n");
        exit(1);
    }
    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
                free(choice);
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
    free(choice);
    return attack;
}

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

void freeButtons(button *buttonArray, int abilities)
{
    int i, j;    
    for(i = 0; i < abilities + 1; i++){
        for(j = 0; j < 2; j++){
            SDL_DestroyTexture(buttonArray[i].buttonTex[j]);
            SDL_FreeSurface(buttonArray[i].buttonSur[j]);
        }
    }
    free(buttonArray);
}



void testDisplayButtons()
{
    button *buttonArray;
    int attack;
    int used[ATTACKCOMBOS] = {1, 10, FILLER, FILLER, FILLER, FILLER, FILLER, FILLER};
    battleState state = PLAYERINPUT;

    display *d = createDisplay(WINDOWWIDTH, WINDOWHEIGHT);
    enemy *e = createEnemy(8);
    currentBattle *battle = createBattle(d, e);
    RenderRefresh(d, battle);
    SDL_RenderPresent(d->ren);

    buttonArray = createButtons(3, d);
    attack = renderButtons(buttonArray, 3, used, d, &state, battle);
    fprintf(stdout, "Used attack %d\n", attack);
    freeButtons(buttonArray, 3);

    freeBattle(battle);
    free(e);
    closeDisplay(d);
    succeed("Buttons ok");
}
