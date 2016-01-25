#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720
#define WALKING_ANIMATION_FRAMES 9

struct windows
    {
    SDL_Window* gWindow;
    SDL_Renderer* gRenderer;
    SDL_Texture* newTexture;
    SDL_Surface* loadedSurface;
    SDL_Texture* mTexture;
    SDL_Event e;
    SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
    };
typedef struct windows Windows;

void initiate (Windows* p);
void close_all (Windows* p);
void fillclips (Windows* p);
void set_attributes(Windows *p, int *mWidth, int *mHeight);
void render_fireball(Windows *p, int *mWidth, int *mHeight, int x, int y);

int main(void)
{
int mWidth = 0, mHeight = 0, x = 0, y = 0;
Windows *pointer = (Windows*)malloc(sizeof(Windows));

SDL_Init(SDL_INIT_EVERYTHING);
initiate(pointer);
set_attributes(pointer, &mWidth, &mHeight);
fillclips(pointer);
render_fireball(pointer, &mWidth, &mHeight, x, y);
close_all(pointer);

return 0;
}

void initiate (Windows* p)
{
    p->gWindow = NULL; 
    p->gRenderer = NULL;
    p->newTexture = NULL;
    p->loadedSurface = IMG_Load("./lighteningball.bmp"); 
    p->mTexture = NULL;
}

void set_attributes(Windows *p, int *mWidth, int *mHeight)
{
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    p->gWindow = SDL_CreateWindow( "Fireball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    SDL_SetColorKey( p->loadedSurface, SDL_TRUE, SDL_MapRGB(p->loadedSurface->format, 0, 0, 0 )); 
    p->gRenderer = SDL_CreateRenderer( p->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );  
    SDL_SetRenderDrawColor( p->gRenderer, 0, 0, 0, 0 );
    SDL_SetColorKey( p->loadedSurface, SDL_TRUE, SDL_MapRGB(p->loadedSurface->format, 0, 0, 0 ));
    p->newTexture = SDL_CreateTextureFromSurface(p->gRenderer, p->loadedSurface);
    *mWidth = p->loadedSurface->w;
    *mHeight = p->loadedSurface->h;    
    p->mTexture = p->newTexture;
}

void fillclips(Windows* p)
{
    
    p->gSpriteClips[ 0 ].x =   0; 
    p->gSpriteClips[ 0 ].y =   0;
    p->gSpriteClips[ 0 ].w =  250;
    p->gSpriteClips[ 0 ].h = 250;

    p->gSpriteClips[ 1 ].x =  250;
    p->gSpriteClips[ 1 ].y =   0;
    p->gSpriteClips[ 1 ].w =  250;
    p->gSpriteClips[ 1 ].h = 250;
		
    p->gSpriteClips[ 2 ].x = 500;
    p->gSpriteClips[ 2 ].y =   0;
    p->gSpriteClips[ 2 ].w =  250;
    p->gSpriteClips[ 2 ].h = 250;

    p->gSpriteClips[ 3 ].x = 750;
    p->gSpriteClips[ 3 ].y =   0;
    p->gSpriteClips[ 3 ].w =  250;
    p->gSpriteClips[ 3 ].h = 250;
	
    p->gSpriteClips[ 4 ].x = 1000;
    p->gSpriteClips[ 4 ].y =   0;
    p->gSpriteClips[ 4 ].w =  250;
    p->gSpriteClips[ 4 ].h = 250;
    
    p->gSpriteClips[ 5 ].x = 1250;
    p->gSpriteClips[ 5 ].y =   0;
    p->gSpriteClips[ 5 ].w =  250;
    p->gSpriteClips[ 5 ].h = 250;

    p->gSpriteClips[ 6 ].x = 1500;
    p->gSpriteClips[ 6 ].y =   0;
    p->gSpriteClips[ 6 ].w =  250;
    p->gSpriteClips[ 6 ].h = 250;
    
    p->gSpriteClips[ 7 ].x = 1750;
    p->gSpriteClips[ 7 ].y =   0;
    p->gSpriteClips[ 7 ].w =  250;
    p->gSpriteClips[ 7 ].h = 250;

    p->gSpriteClips[ 8 ].x = 2000;
    p->gSpriteClips[ 8 ].y =   0;
    p->gSpriteClips[ 8 ].w =  250;
    p->gSpriteClips[ 8 ].h = 250;
    
    p->gSpriteClips[ 9 ].x = 2000;
    p->gSpriteClips[ 9 ].y =   0;
    p->gSpriteClips[ 9 ].w =  250;
    p->gSpriteClips[ 9 ].h = 250;
    
}

void render_fireball(Windows *p, int *mWidth, int *mHeight, int x, int y)
{
int frame = 0, i;

for (i = 0; i <= 180; i++) /* 180 cycles of rendering = ~ 5 seconds animation time */
    {        
        SDL_SetRenderDrawColor( p->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( p->gRenderer );
        SDL_Rect* clip = NULL; /* current clip */
        clip = &p->gSpriteClips[ frame / 9 ]; /*set where clip looks at on bmp */
        SDL_Rect renderQuad = {x, y, *mWidth, *mHeight}; /* set rectangle corners*/
        renderQuad.w = (clip->w);
        renderQuad.h = (clip->h); /* w/h from gsprite clips */
        SDL_RenderCopy(p->gRenderer, p->mTexture, clip, &renderQuad); 
        SDL_RenderPresent(p->gRenderer); /* update screen */
        ++frame;
        
        if( frame / 9 >= WALKING_ANIMATION_FRAMES )
        {
            frame = 0;
        }
    }
}

void close_all (Windows* p)
{
    SDL_DestroyRenderer(p->gRenderer);
    SDL_DestroyWindow(p->gWindow);
    p->gWindow = NULL;
    p->gRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
    
