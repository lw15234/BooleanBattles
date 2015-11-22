#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WALKING_ANIMATION_FRAMES 6

int main(void)
{
/* variables which can be adjusted*/

int frame = 0;
int attacking = 1; /* will be fed by main program */
int mWidth = 0;
int mHeight = 0; /* images dimensions */
int x = 0; 
int y = 0; /* sdl rect stuff */

/* init function */
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* gWindow = NULL; 
SDL_Renderer* gRenderer = NULL;
SDL_Texture* newTexture = NULL;
SDL_Surface* loadedSurface = IMG_Load("./cartoon_fireball.bmp"); 
SDL_Texture* mTexture = NULL;
SDL_Event e;

/* windows n shit */
SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
gWindow = SDL_CreateWindow( "Iceball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );

/* load from file function + sprite attributes */
SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0 )); /* ignore colours in background of sprite sheet */
newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
mWidth = loadedSurface->w;
mHeight = loadedSurface->h;    
SDL_FreeSurface(loadedSurface);
mTexture = newTexture;

/* rendering */
SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
 
/* sprite locations - can be hard coded to a location on the screen */

		gSpriteClips[ 0 ].x =   0;
		gSpriteClips[ 0 ].y =   0;
		gSpriteClips[ 0 ].w =  250;
		gSpriteClips[ 0 ].h = 356;

		gSpriteClips[ 1 ].x =  250;
		gSpriteClips[ 1 ].y =   0;
		gSpriteClips[ 1 ].w =  250;
		gSpriteClips[ 1 ].h = 356;
		
		gSpriteClips[ 2 ].x = 500;
		gSpriteClips[ 2 ].y =   0;
		gSpriteClips[ 2 ].w =  250;
		gSpriteClips[ 2 ].h = 356;

		gSpriteClips[ 3 ].x = 717;
		gSpriteClips[ 3 ].y =   0;
		gSpriteClips[ 3 ].w =  250;
		gSpriteClips[ 3 ].h = 356;
	
        gSpriteClips[ 4 ].x = 954;
		gSpriteClips[ 4 ].y =   0;
		gSpriteClips[ 4 ].w =  250;
		gSpriteClips[ 4 ].h = 356;
    
        gSpriteClips[ 5 ].x = 1201;
		gSpriteClips[ 5 ].y =   0;
		gSpriteClips[ 5 ].w =  250;
		gSpriteClips[ 5 ].h = 356;
        
        gSpriteClips[ 6 ].x = 1500;
		gSpriteClips[ 6 ].y =   0;
		gSpriteClips[ 6 ].w =  250;
		gSpriteClips[ 6 ].h = 356;

/* main loop */
    while(attacking)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
            attacking = 0;
            }
        }
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        /* Render current frame */
        SDL_Rect* clip = NULL;
        clip = &gSpriteClips[ frame / 6 ];
        SDL_Rect renderQuad = {x, y, mWidth, mHeight};
        renderQuad.w = ((clip->w));
        renderQuad.h = ((clip->h));
        SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
        
        /* Update screen */
        SDL_RenderPresent( gRenderer );

        /* Go to next frame */
        ++frame;

        /* Cycle */
        if( frame / 6 >= WALKING_ANIMATION_FRAMES )
        {
            frame = 0;
        }
    }
        
/* Free resources and close SDL */
SDL_DestroyRenderer( gRenderer );
SDL_DestroyWindow( gWindow );
gWindow = NULL;
gRenderer = NULL;
IMG_Quit();
SDL_Quit();

return 0;
}
