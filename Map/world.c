#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

/* Screen dimension constants */
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

bool init(); //Starts up SDL and creates window
bool loadMedia(); //Loads media
void close(); //Frees media and shuts down SDL

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gBoolBattles = NULL;

//The player character
SDL_Surface* gplayer = NULL;

int main(int argc, char* args[]) {

	//Start up SDL and create window
	if(!init()) {
        printf( "Failed to initialize!\n" );
        } else {
            //Load media
            if(!loadMedia()) {
	        printf( "Failed to load media!\n" );
	        } else {
	            //Main loop flag
	            bool quit = false;

	            //Event handler
	            SDL_Event e;

	            while(!quit) {
                    //Handle events on queue
                while(SDL_PollEvent( &e ) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
				}
				//Apply the image
				SDL_BlitSurface(gBoolBattles, NULL, gScreenSurface, NULL);
				SDL_BlitSurface(gplayer, NULL, gBoolBattles, NULL);

				//Update the surface
				SDL_UpdateWindowSurface(gWindow);
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Boolean Battles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia() {

	//Loading success flag
	bool success = true;

	//Load splash image
	gBoolBattles = SDL_LoadBMP("world.bmp");
	gplayer = SDL_LoadBMP("player.bmp");
	if(gBoolBattles == NULL || gplayer == NULL) {
        printf("Unable to load images %s! SDL Error: %s\n", "player.bmp", SDL_GetError());
		success = false;
	}
	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface(gBoolBattles);
	SDL_FreeSurface(gplayer);
	gBoolBattles = NULL;
	gplayer = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
