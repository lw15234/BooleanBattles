#include <SDL/SDL.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SPRITE_SIZE    32

int main ( int argc, char *argv[] )
{
  SDL_Surface *screen, *temp, *sprite, *grass, *enemy;
  SDL_Rect rcSprite, rcGrass, rcenemy;
  SDL_Event event;
  Uint8 *keystate;

  int colorkey, gameover;

  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Move", "SDL Move");

  /* create window */
  screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* load sprite */
  temp   = SDL_LoadBMP("stickman.bmp");
  sprite = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* setup sprite colorkey and turn on RLE */
  colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
  SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

  /* load grass */
  temp  = SDL_LoadBMP("background.bmp");
  grass = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
  
  /* load enemy */
  temp = SDL_LoadBMP("enemy.bmp");
  enemy = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* set sprite position */
  rcSprite.x = 0;
  rcSprite.y = (SCREEN_HEIGHT/2);

  /* set enemy position */
  rcenemy.x = 450;
  rcenemy.y = (SCREEN_HEIGHT/2);
  
  gameover = 0;

  /* message pump */
  while (!gameover)
  {
    /* look for an event */
    if (SDL_PollEvent(&event)) {
      /* an event was found */
      switch (event.type) {
        /* close button clicked */
        case SDL_QUIT:
          gameover = 1;
          break;

        /* handle the keyboard */
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
            case SDLK_q:
              gameover = 1;
              break;
          }
          break;
      }
    }

    /* handle sprite movement */
    keystate = SDL_GetKeyState(NULL);
    if (keystate[SDLK_LEFT] ) {
      rcSprite.x -= 1;
    }
    if (keystate[SDLK_RIGHT] ) {
      rcSprite.x += 1;
    }
    
    /* handle collision with edges of screen */
    if ( rcSprite.x == SCREEN_HEIGHT ) {
      rcSprite.x = 0;
    }
    else if ( rcSprite.x > SCREEN_WIDTH-SPRITE_SIZE ) {
      rcSprite.x = SCREEN_WIDTH-SPRITE_SIZE;
    }
    if ( rcSprite.y == SCREEN_WIDTH ) {
      rcSprite.y = 0;
    }
    else if ( rcSprite.y > SCREEN_HEIGHT-SPRITE_SIZE ) {
      rcSprite.y = SCREEN_HEIGHT-SPRITE_SIZE;
    }

    /* draw the background */
 
    SDL_BlitSurface(grass, NULL, screen, NULL);
      
    
    /* draw the sprite & draw the enemy */
    SDL_BlitSurface(sprite, NULL, screen, &rcSprite);
    SDL_BlitSurface(enemy, NULL, screen, &rcenemy);

    /* update the screen */
    SDL_UpdateRect(screen, 0, 0, 0, 0);
  }

  /* close down */
  SDL_FreeSurface(sprite);
  SDL_FreeSurface(enemy);
  SDL_FreeSurface(grass);
  SDL_Quit();

  return 0;
}
