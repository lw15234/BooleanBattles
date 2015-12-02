#include "attackAnimation.h"
#include "SDL.h"
#include <math.h>

#define FRAMES 10

typedef struct projectile{
    SDL_Texture *tex;
    SDL_Texture *nextTex;
    SDL_Surface *sur;
    SDL_Rect spriteClips[FRAMES];
}projectile;

typedef struct display{
    int width, height;
    SDL_Window *win;
    SDL_Surface *sur;
    SDL_Renderer *ren;
    SDL_Event *e;
}display;

projectile *createProjectile();
void destroyProjectile(projectile *p);
void renderAttack(int attack, projectile *p, SDL_Renderer *ren);
void selectAttack(int attack, projectile *p);
void setAttackAttr(projectile *p, SDL_Renderer *ren);
void fillClips(projectile *p);
void animateAttack(projectile *p, SDL_Renderer *ren, int width, int height);


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

void attackManager(int attack, SDL_Renderer *ren)
{
    int i;

    projectile *p = createProjectile();
    fillClips(p);

    if(attack == 0){
        renderAttack(3, p, ren);
    }
    else{
        for(i = 0; i < 3; i++){
            if((attack / (int)pow(10, i)) % 10){
                renderAttack(i, p, ren);
            }
        }
    }
    destroyProjectile(p);
}

void renderAttack(int attack, projectile *p, SDL_Renderer *ren)
{
    int height = 250, width = 250;
    selectAttack(attack, p);
    setAttackAttr(p, ren);
    animateAttack(p, ren, width, height);
}

void selectAttack(int attack, projectile *p)
{
	switch(attack){
        case 0:
            p->sur = SDL_LoadBMP("projectiles/fire.bmp");
            break;
        case 1:
            p->sur = SDL_LoadBMP("projectiles/ice.bmp");
            break;
        case 2:
            p->sur = SDL_LoadBMP("projectiles/lightning.bmp");
            break;
        case 3:
            p->sur = SDL_LoadBMP("projectiles/normal.bmp");
            break;
    }
}

void setAttackAttr(projectile *p, SDL_Renderer *ren)
{
    p->nextTex = SDL_CreateTextureFromSurface(ren, p->sur);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
    p->tex = p->nextTex;
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

void animateAttack(projectile *p, SDL_Renderer *ren, int width, int height)
{
    int i;
    SDL_Rect *clip = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    SDL_Rect renderQuad = {0, 0, width, height};
    Uint32 t;

    for(i = 0; i < 500; i++){
        clip = &p->spriteClips[i % FRAMES];
        renderQuad.x = i * 10;
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
        SDL_RenderCopy(ren, p->tex, clip, &renderQuad);
        SDL_RenderPresent(ren);
        t = SDL_GetTicks();
        SDL_Delay(20 - (t % 20));
    }
    free(clip);
}
