#include "entity.h"

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

entity *createEntity(char *filename, int x, int y, int w, int h, display *d);

currentBattle *createBattle(display *d, enemy *e)
{
    currentBattle *battle = (currentBattle *)malloc(sizeof(currentBattle));
    if(battle == NULL){
        fprintf(stderr, "Could not free space for battle\n");
        exit(1);
    }
    battle->sur = SDL_LoadBMP(e->background);
    battle->tex = SDL_CreateTextureFromSurface(d->ren, battle->sur);
    battle->hero = createEntity("enemies/hero.bmp", 50, 350, 200, 300, d);
    battle->enemy = createEntity(e->enemySprite, 750, 150, 350, 500, d);
    battle->question = createEntity(e->question, 300, 50, 500, 75, d);
    battle->dialogue = createEntity(e->dialogue, 400, 60, 500, 300, d);

    return battle;
}

entity *createEntity(char *filename, int x, int y, int w, int h, display *d)
{
    entity *ent = (entity*)malloc(sizeof(entity));
    if(ent == NULL){
        fprintf(stderr, "Could not free space for entity\n");
        exit(1);
    }
    ent->entityPos.x = x;
    ent->entityPos.y = y;
    ent->entityPos.w = w;
    ent->entityPos.h = h;
    ent->entitySur = SDL_LoadBMP(filename);
    SDL_SetColorKey( ent->entitySur, SDL_TRUE, SDL_MapRGB(ent->entitySur->format, 228, 129, 250 ));
    ent->entityTex = SDL_CreateTextureFromSurface(d->ren, ent->entitySur);
    return ent;
}

void RenderRefresh(display *d, currentBattle *battle)
{
    SDL_RenderClear(d->ren);
    SDL_RenderCopy(d->ren, battle->tex, NULL, NULL);
    SDL_RenderCopy(d->ren, battle->hero->entityTex, NULL, &battle->hero->entityPos);
    SDL_RenderCopy(d->ren, battle->enemy->entityTex, NULL, &battle->enemy->entityPos);
    SDL_RenderCopy(d->ren, battle->question->entityTex, NULL, &battle->question->entityPos);
    SDL_RenderCopy(d->ren, battle->dialogue->entityTex, NULL, &battle->dialogue->entityPos);
}

void freeBattle(currentBattle *battle)
{
    SDL_DestroyTexture(battle->hero->entityTex);
    SDL_DestroyTexture(battle->enemy->entityTex);
    SDL_DestroyTexture(battle->tex);
    SDL_FreeSurface(battle->hero->entitySur);
    SDL_FreeSurface(battle->enemy->entitySur);
    SDL_FreeSurface(battle->sur);
    free(battle->hero);
    free(battle->enemy);
    free(battle);
}



void testEntity()
{
    display *d = createDisplay(WINDOWWIDTH, WINDOWHEIGHT);
    enemy *e = createEnemy(8);

    currentBattle *battle = createBattle(d, e);
    RenderRefresh(d, battle);
    SDL_RenderPresent(d->ren);
    SDL_Delay(2000);
    freeBattle(battle);

    free(e);
    closeDisplay(d);
    succeed("Entity ok");
}
