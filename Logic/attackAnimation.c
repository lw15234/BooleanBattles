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
void attackManager(int attack, display *d);
void renderAttack(int attack, projectile *p, display *d);
void selectAttack(int attack, projectile *p);
void setAttackAttr(projectile *p, display *d);
void fillClips(projectile *p);
void animateAttack(projectile *p, display *d, int width, int height);

display *createDisplay(int width, int height);
void closeDisplay(display *d);

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

void attackManager(int attack, display *d)
{
    int i;

    projectile *p = createProjectile();
    fillClips(p);

    if(attack == 0){
        renderAttack(3, p, d);
    }
    else{
        for(i = 0; i < 3; i++){
            if((attack / (int)pow(10, i)) % 10){
                renderAttack(i, p, d);
            }
        }
    }
    destroyProjectile(p);
}

void renderAttack(int attack, projectile *p, display *d)
{
    int height = 250, width = 250;
    selectAttack(attack, p);
    setAttackAttr(p, d);
    animateAttack(p, d, width, height);
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

void setAttackAttr(projectile *p, display *d)
{
    p->nextTex = SDL_CreateTextureFromSurface(d->ren, p->sur);
    SDL_SetRenderDrawColor(d->ren, 255, 255, 255, 0);
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

void animateAttack(projectile *p, display *d, int width, int height)
{
    int i;
    clip = (SDL_Rect *)malloc(sizeof(SDL_Rect));
    SDL_Rect *clip = NULL;
    SDL_Rect renderQuad = {0, 0, width, height};
    Uint32 t;

    for(i = 0; i < 500; i++){
        clip = &p->spriteClips[i % FRAMES];
        renderQuad.x = i * 10;
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
        SDL_RenderCopy(d->ren, p->tex, clip, &renderQuad);
        SDL_RenderPresent(d->ren);
        t = SDL_GetTicks();
        SDL_Delay(20 - (t % 20));
    }
    free(clip);
}

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
    d->ren = SDL_CreateRenderer(d->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderPresent(d->ren);
    return d;
}

void closeDisplay(display *d)
{
    SDL_DestroyWindow(d->win);
    SDL_Quit();
    free(d);
    return;
}

int main(void)
{
    display *d = createDisplay(1080, 720);
    attackManager(1, d);
    closeDisplay(d);
    return 0;
}
