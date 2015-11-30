#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h">
#include "hero.h"

const float SPEED_X = 0.1;
const float SPEED_Y = 0.1;

void HeroInit(Hero* hero, Rect worldRect, SDL_Rect textureRect, SDL_Texture* texture) {
	memcpy(&hero->worldRect, &worldRect, sizeof(Rect));
	hero->displayRect.x = (int)hero->worldRect.x - (int)(hero->worldRect.w / 2);
	hero->displayRect.y = (int)hero->worldRect.y - (int)(hero->worldRect.h / 2);
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
	hero->displayRect.x = (int)hero->worldRect.x - (int)(hero->worldRect.w / 2);
}

void HeroMoveRight(Hero* hero) {
	hero->worldRect.x += SPEED_X;
	hero->displayRect.x = (int)hero->worldRect.x - (int)(hero->worldRect.w / 2);
}

void HeroMoveUp(Hero* hero) {
	hero->worldRect.y -= SPEED_Y;
	hero->displayRect.y = (int)hero->worldRect.y - (int)(hero->worldRect.h / 2);
}

void HeroMoveDown(Hero* hero) {
	hero->worldRect.y += SPEED_Y;
	hero->displayRect.y = (int)hero->worldRect.y - (int)(hero->worldRect.h / 2);
}

SDL_Rect HeroCalcNewPosition(const Hero* hero, bool up, bool down, bool left, bool right) {
    SDL_Rect result;
    float x, y;
    x = hero->worldRect.x;
    y = hero->worldRect.y;
    if(up) {
        y -= SPEED_Y;
    }
    if(down) {
        y += SPEED_Y;
    }
    if(left) {
        x -= SPEED_X;
    }
    if(right) {
        x += SPEED_X;
    }
    result.w = hero->worldRect.w;
    result.h = hero->worldRect.h;
    result.x = x;
    result.y = y;
    return result;
}
