struct currentBattle{
	entity *hero, *enemy;
	SDL_Surface;
	SDL_Texture;
}

struct entity{
	SDL_Rect entityPos;
	SDL_Texture *entityTex;
	SDL_Surface *entitySur;
}

entity *createEntity(char *filename, int x, int y, int w, int h, display *d)
{
	entity *ent = (entity*)malloc(sizeof(entity));
	ent->entityPos.x = x;
	ent->entityPos.y = y;
	ent->entityPos.w = w;
	ent->entityPos.h = h;
	ent->entitySur = LoadBMP("filename");
	ent->entityTex = SDL_CreateTextureFromSurface(d->ren, ent->entitySur);
	return ent;
}
/*If we use the level as an additional arguement we can chose the enemy and the background in this function. We will also need the pointer to the hero and the enemy*/
void createBattle(display *d, currentBattle *battle)
{
	battle->SDL_Surface *backgroundSur = NULL;
	battle->SDL_Texture *backgroundTex = NULL;
	battle->entity *hero, *enemy;
	
	backgroundSur = SDL_LoadBMP("background.bmp");
	backgroundTex = SDL_CreateTextureFromSurface(d->ren, backgroundSur);
	
	hero = createEntity("hero.bmp", 100, 100, 100, 100, d);
	enemy = createEntity("enemy.bmp", 500, 100, 100, 100, d);
}

void RenderRefresh(display *d, currentBattle battle)
{
	SDL_RenderClear(d->ren);
	SDL_RenderCopy(d->ren, battle->backgroundTex, NULL, NULL);
	SDL_RenderCopy(d->ren, battle->hero->entityTex, NULL, battle->hero->&entityPos);
	SDL_RenderCopy(d->ren, battle->enemy->entityTex, NULL, battle->enemy->&entityPos);
	SDL_RenderPresent(d->ren);
}
