typedef struct projectile{
    SDL_Texture *tex;
    SDL_Texture *nextTex;
    SDL_Surface *sur;
    SDL_Rect spriteClips[ANIM_FRAMES];
}projectile;

projectile *createProjectile(){
    projectile *p = (projectile *)malloc(sizeof(projectile));
    p->tex = NULL;
    p->newTex = NULL;
    p->sur = NULL;
    return p;
}

destroyProjectile(projectile *p){
    SDL_FreeSurface(p->sur);
    free(p);
    return;
}

void attackManager(int attack, display *d)
{
    int i;

    projectile *p = createProjectile();

    if(attack == 0){
        someattackfunction(3, d);
    }
    else{
        for(i = 0; i < 3; i++){
            if((attack / pow(10, i)) % 10){
                renderAttack(i, p, d);
            }
        }
    }
    destroyProjectile(p);
}

void renderAttack(int attack, projectile *p, display *d)
{
	switch(attack){
        case 0:
            p->sur = IMG_Load("projectiles/fire.bmp");
            break;
        case 1:
            p->sur = IMG_Load("projectiles/ice.bmp");
            break;
        case 2:
            p->sur = IMG_Load("projectiles/lightning.bmp");
            break;
        case 3:
            p->sur = IMG_Load("projectiles/normal.bmp");
            break;
    }
}



