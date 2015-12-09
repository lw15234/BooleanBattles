// https://wiki.libsdl.org/SDL_RenderCopy

#include "SDL.h"
#define SHAPE_SIZE 16


enum { heroImage_x = 32, heroImage_y = 48 };

int main(void)
{
  SDL_Window* Main_Window;
  SDL_Renderer* Main_Renderer;
  SDL_Surface* Loading_Surf;
  SDL_Texture* Background_Tx;
  SDL_Texture* BlueShapes;

  /* Rectangles for drawing which will specify source (inside the texture)
  and target (on the screen) for rendering our textures. */
  SDL_Rect SrcR;
  SDL_Rect DestR;

  SrcR.x = 500;
  SrcR.y = 300;
  SrcR.w = SHAPE_SIZE;
  SrcR.h = SHAPE_SIZE;


  DestR.x = 640 / 2 - SHAPE_SIZE / 2;
  DestR.y = 580 / 2 - SHAPE_SIZE / 2;
  DestR.w = SHAPE_SIZE;
  DestR.h = SHAPE_SIZE;


  /* Before we can render anything, we need a window and a renderer */
  Main_Window = SDL_CreateWindow("SDL_RenderCopy Example",
  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1080, 720, 0);
  Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

  /* The loading of the background texture. Since SDL_LoadBMP() returns
  a surface, we convert it to a texture afterwards for fast accelerated
  blitting. */
  Loading_Surf = SDL_LoadBMP("Map_level_10.bmp");
  Background_Tx = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
  SDL_FreeSurface(Loading_Surf); /* we got the texture now -> free surface */

  /* Load an additional texture */
  Loading_Surf = SDL_LoadBMP("hero1_back_01.bmp");
  BlueShapes = SDL_CreateTextureFromSurface(Main_Renderer, Loading_Surf);
  SDL_FreeSurface(Loading_Surf);

  /* now onto the fun part.
  This will render a rotating selection of the blue shapes
  in the middle of the screen 
  int i;
  int n;
  for (i = 0; i < 2; ++i) {
    for(n = 0; n < 4; ++n) {
      SrcR.x = SHAPE_SIZE * (n % 2);
      if (n > 1) {
        SrcR.y = SHAPE_SIZE;
      } else {
        SrcR.y = 0;
      }

      
    }
  }
*/
/* render background, whereas NULL for source and destination
      rectangles just means "use the default" */
      SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL);

      /* render the current animation step of our shape */
      SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
      SDL_RenderPresent(Main_Renderer);
      SDL_Delay(500);

  /* The renderer works pretty much like a big canvas:
  when you RenderCopy() you are adding paint, each time adding it
  on top.
  You can change how it blends with the stuff that
  the new data goes over.
  When your 'picture' is complete, you show it
  by using SDL_RenderPresent(). */

  /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
  from 1.2 surfaces and blitting, think of the renderer as your
  main surface, and SDL_RenderCopy() as the blit function to that main
  surface, with SDL_RenderPresent() as the old SDL_Flip() function.*/

  SDL_DestroyTexture(BlueShapes);
  SDL_DestroyTexture(Background_Tx);
  SDL_DestroyRenderer(Main_Renderer);
  SDL_DestroyWindow(Main_Window);
  SDL_Quit();


  return 0;
}

