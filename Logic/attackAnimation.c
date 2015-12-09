#include "attackAnimation.h"
#include "SDL.h"
#include <math.h>

#define FRAMES 9
#define FRAMEDELAY 20 /*Lower this for quicker testing*/
#define WIDTH 250
#define HEIGHT 250
#define XPOS 250
#define YPOS 360
#define SPEED 20
#define LENGTH 100
#define REFLECTION 20

typedef struct projectile{
    SDL_Texture *tex;
    SDL_Texture *nextTex;
    SDL_Surface *sur;
    SDL_Rect spriteClips[FRAMES];
}projectile;


projectile *createProjectile();
void destroyProjectile(projectile *p);
void renderAttack(int attack, projectile *p, display *d, int success, currentBattle *battle);
void selectAttack(int attack, projectile *p);
void setAttackAttr(projectile *p, display *d);
void fillClips(projectile *p);
void animateAttack(projectile *p, display *d, int success, currentBattle *battle);


projectile *createProjectile(){
    projectile *p = (projectile *)malloc(sizeof(projectile));
    if(p == NULL){
        fprintf(stderr, "Failed to malloc projectile\n");
        exit(1);
    }
    p->tex = NULL;
    p->nextTex = NULL;
    p->sur = NULL;
    return p;
}

void destroyProjectile(projectile *p){
    SDL_FreeSurface(p->sur);
    free(p);
    return;
}

void attackManager(int attack, display *d, int success, currentBattle *battle)
{
    int i;

    projectile *p = createProjectile();
    fillClips(p);

    if(attack == 0){
        renderAttack(3, p, d, success, battle);
    }
    else{
        for(i = 0; i < 3; i++){
            if((attack / (int)pow(10, i)) % 10){
                renderAttack(i, p, d, success, battle);
            }
        }
    }
    destroyProjectile(p);
}

void renderAttack(int attack, projectile *p, display *d, int success, currentBattle *battle)
{
    selectAttack(attack, p);
    setAttackAttr(p, d);
    animateAttack(p, d, success, battle);
}

void selectAttack(int attack, projectile *p)
{
	switch(attack){
        case 0:
            p->sur = SDL_LoadBMP("projectiles/fire.bmp");
            if(!p->sur){
                printf("Could not load file: %s\n", SDL_GetError());
                exit(1);
            }
            break;
        case 1:
            p->sur = SDL_LoadBMP("projectiles/ice.bmp");
            if(!p->sur){
                printf("Could not load file: %s\n", SDL_GetError());
                exit(1);
            }
            break;
        case 2:
            p->sur = SDL_LoadBMP("projectiles/lightning.bmp");
            if(!p->sur){
                printf("Could not load file: %s\n", SDL_GetError());
                exit(1);
            }
            break;
        case 3:
            p->sur = SDL_LoadBMP("projectiles/normal.bmp");
            if(!p->sur){
                printf("Could not load file: %s\n", SDL_GetError());
                exit(1);
            }
            break;
    }
}

void setAttackAttr(projectile *p, display *d)
{
    SDL_SetColorKey(p->sur, SDL_TRUE, SDL_MapRGB(p->sur->format, 228, 129, 250));
    p->tex = SDL_CreateTextureFromSurface(d->ren, p->sur);    
}

void fillClips(projectile *p)
{
    int i;
    for(i = 0; i < FRAMES; i++){
        p->spriteClips[i].x = 250 * i;
        p->spriteClips[i].y = 0;
        p->spriteClips[i].w = 250;
        p->spriteClips[i].h = 250;
    }
}

void animateAttack(projectile *p, display *d, int success, currentBattle *battle)
{
    int i;
    SDL_Rect *clip = NULL;
    SDL_Rect renderQuad = {XPOS, YPOS, WIDTH, HEIGHT};
    Uint32 t;

    if(success){
        for(i = 0; i < LENGTH; i++){
            SDL_RenderClear(d->ren);
            RenderRefresh(d, battle);
            clip = &p->spriteClips[i % FRAMES];
            renderQuad.x = XPOS + i * SPEED;
            SDL_RenderCopy(d->ren, p->tex, clip, &renderQuad);
            SDL_RenderPresent(d->ren);
            t = SDL_GetTicks();
            SDL_Delay(FRAMEDELAY - (t % FRAMEDELAY));
        }
    }
    else{
        for(i = 0; i < REFLECTION; i++){
            SDL_RenderClear(d->ren);
            RenderRefresh(d, battle);
            clip = &p->spriteClips[i % FRAMES];
            renderQuad.x = XPOS + i * SPEED;
            SDL_RenderCopy(d->ren, p->tex, clip, &renderQuad);
            SDL_RenderPresent(d->ren);
            t = SDL_GetTicks();
            SDL_Delay(FRAMEDELAY - (t % FRAMEDELAY));
        }
        for(i = REFLECTION; i < LENGTH; i++){
            SDL_RenderClear(d->ren);
            RenderRefresh(d, battle);
            clip = &p->spriteClips[i % FRAMES];
            renderQuad.x = XPOS + (2 * REFLECTION - i) * SPEED;
            SDL_RenderCopy(d->ren, p->tex, clip, &renderQuad);
            SDL_RenderPresent(d->ren);
            t = SDL_GetTicks();
            SDL_Delay(FRAMEDELAY - (t % FRAMEDELAY));
        }        
    }
}



void testAttackAnimation()
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
    attackManager(attack, d, 1, battle);
    attack = renderButtons(buttonArray, 3, used, d, &state, battle);
    attackManager(attack, d, 0, battle);

    freeButtons(buttonArray, 3);
    freeBattle(battle);
    free(e);
    closeDisplay(d);
    succeed("Animation ok");
}
