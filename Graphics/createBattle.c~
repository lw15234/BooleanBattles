

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

void createBattle(display *d, char *filename)
{
	SDL_Surface *background = NULL;
	SDL_Texture *backgroundTex = NULL;
	entity hero, enemy;
	
	background = SDL_LoadBMP(filename);
	backgroundTex = SDL_CreateTextureFromSurface(d->ren, background);
	
	hero = createEntity("hero.bmp", 0, 0, 100, 100, d);
	enemy = createEntity("enemy.bmp", 0, 0, 100, 100, d);

	SDL_RenderClear(d->ren);
	SDL_RenderCopy(d->ren, backgroundTex, NULL, NULL);
	SDL_RenderCopy(d->ren, hero->entityTex, NULL, hero->&entityPos);
	SDL_RenderCopy(d->ren, enemy->entityTex, NULL, enemy->&entityPos);
	SDL_RenderPresent(d->ren)
}
