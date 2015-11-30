#ifndef _HERO_H_INCLUDED
#define _HERO_H_INCLUDED

#include <SDL2/SDL.h>
#include "util.h"


typedef struct Hero Hero;

/*Represents Hero
 * pos - position of hero in world coordinates
 * displayRect - size and position of hero on screen
 * textureRect - rect which contains hero image on texture
 * texture - texture containing hero image
 */

struct Hero {
	Rect worldRect;
	SDL_Rect displayRect;
	SDL_Rect textureRect;
	SDL_Texture* texture;
};

void HeroInit(Hero* hero, Rect worldRect, SDL_Rect textureRect, SDL_Texture* texture);
void HeroRender(const Hero* hero, SDL_Renderer* renderer);
SDL_Rect HeroCalcNewPosition(const Hero* hero, bool up, bool down, bool left, bool right);
void HeroMoveLeft(Hero* hero);
void HeroMoveRight(Hero* hero);
void HeroMoveUp(Hero* hero);
void HeroMoveDown(Hero* hero);

#endif
