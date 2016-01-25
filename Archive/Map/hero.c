#include <stdio.h>
#include <string.h>
#include "SDL2/include/SDL.h"
#include "hero.h"

const float SPEED_X = 0.1;
const float SPEED_Y = 0.1;

void HeroInit(Hero* hero, Rect worldRect, SDL_Rect textureRect, SDL_Texture* texture) {
	memcpy(&hero->worldRect, &worldRect, sizeof(Rect));
	hero->displayRect.x = (int)hero->worldRect.x;
	hero->displayRect.y = (int)hero->worldRect.y;
	hero->displayRect.w = (int)hero->worldRect.w;
	hero->displayRect.h = (int)hero->worldRect.h;
	memcpy(&hero->textureRect, &textureRect, sizeof(SDL_Rect));
	hero->texture = texture;
}
void HeroRender(const Hero* hero, SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, hero->texture, &hero->textureRect, &hero->displayRect);
}

void HeroMoveLeft(Hero* hero) {
	hero->worldRect.x -= SPEED_X;
	hero->displayRect.x = (int)hero->worldRect.x;
}

void HeroMoveRight(Hero* hero) {
	hero->worldRect.x += SPEED_X;
	hero->displayRect.x = (int)hero->worldRect.x;
}

void HeroMoveUp(Hero* hero) {
	hero->worldRect.y -= SPEED_Y;
	hero->displayRect.y = (int)hero->worldRect.y;
}

void HeroMoveDown(Hero* hero) {
	hero->worldRect.y += SPEED_Y;
	hero->displayRect.y = (int)hero->worldRect.y;
}
