/*********************************************
1. import and export values:
This program needs to know where the battle was won.
It exports where the player has reached, before entering the battle.

The buttons on the map requires knowledge about whether a battlefield is unlocked, for every available battlefield. 
It requires to import 3 int arrays:

2. maintenance:
This map is fully functional for the first 2 levels, and part of the 3rd level.
More levels can be added.
It still requires refactoring.

3. copyright notice:
This code contains derivative work of converted C++ code from Lazy Foo tutorials, (http://lazyfoo.net/)
with the author's written permission for non-commercial, educational use.

Images are found from the internet.
Read txt file for more detail.

All other errors are entirely Iguana team's responsibility.



**********************************************/
//#include "yucheng.h"
//#include <string> //C++ header

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>

#define LOCATION_ON_MAP_NUM_MAX 100

//**import values******************************
bool BattleWon = true;

int locationAccess [ LOCATION_ON_MAP_NUM_MAX ]; //which battlefields can the hero now access?
int locationPosition_x [ LOCATION_ON_MAP_NUM_MAX ], locationPosition_y [ LOCATION_ON_MAP_NUM_MAX ]; //what are the battlefields' coordinations on the map?

//**export values******************************
int targetAreaLocation;

int locationAccess [ LOCATION_ON_MAP_NUM_MAX ]; //which battlefields can the hero now access?

/***SELECT FROM OPTIONS*****************************************/
/***SELECT FROM OPTIONS*****************************************/
/***SELECT FROM OPTIONS*****************************************/

//debug?
enum {debug_no, debug_test, debug_total};
const int DEBUG_LEVEL = debug_no;

//Screen dimension constants
enum {mapX = 1032, mapY = 774};
const int SCREEN_WIDTH = mapX;
const int SCREEN_HEIGHT = mapY;

enum { heroImage_x = 32, heroImage_y = 48 };

//map locations
enum {screenBorderLength_left=46, screenBorderLength_right=43, screenBorderLength_up=45, screenBorderLength_down=38};
typedef enum location_t {Gydanhil_x=337, Gydanhil_y=323, //location 0
                         FroastoakVale_x = 432, FroastoakVale_y = 346, //location 1
                         NessusRoad_x = 505, NessusRoad_y = 378 //location 2
                        } location_t;


enum {Gydanhil = 0,
      FroastoakVale = 1,
      NessusRoad = 2
     };

int locationCurrent = 0, locationCap = 0, locationMax = 2;

int sourceAreaLocation; //int targetAreaLocation;

//towards what direction is the hero walking?
enum {map, back, front, left, right, sameDirection};

//SELECT IMAGE NUMBER
enum {worldMap, //0
      hero1_back_01, hero1_back_02, hero1_back_03, hero1_back_04, //1-4
      hero1_front_01, hero1_front_02, hero1_front_03, hero1_front_04, //5-8
      hero1_left_01, hero1_left_02, hero1_left_03, hero1_left_04, //9-12
      hero1_right_01, hero1_right_02, hero1_right_03, hero1_right_04 //13-16
     };

size_t imageUseNumber_current=worldMap, imageUseNumber_total=hero1_front_04;

//***movement variables***************************************************************
//hero's initial position
int heroPosition_x_Initial, heroPosition_y_Initial;
//how far does the hero walk by each step?
enum { walkPace_x = 5, walkPace_y = 5 };

//MAP
const char *image_worldMap_name = "worldMap.jpg";

//****Mouse********************************************************
//Button constants
const int BUTTON_WIDTH = 15;
const int BUTTON_HEIGHT = 15;
//const int TOTAL_BUTTONS = 4;

//where is the mouse button?
SDL_Point mButtonPosition;

//enumerate all possible states for mouse to be pressed
enum {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

//How is the mouse pressed?
int mCurrentState = BUTTON_SPRITE_MOUSE_OUT;

/***DECLARE VARIABLES*****************************************/
/***DECLARE VARIABLES*****************************************/
/***DECLARE VARIABLES*****************************************/

/****INITIAL*************************************/
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

/***IMAGE[IN PROGRESS]********************************************/

/***BMP ERA IMAGE*******************************/
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;
//The image we will load and show on the screen
SDL_Surface* gImageCurrent = NULL;


/***animation*****************************************/
//Walking animation
//const int WALKING_ANIMATION_FRAMES = 4;
//SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
//LTexture gSpriteSheetTexture;

//The window renderer
SDL_Renderer* gRenderer = NULL;


int x;
int y, mWidth, mHeight;
SDL_Rect* clip;
SDL_Texture* mTexture;


//what's the windows's width and heigth?
int getWidth();
int getHeight();


//The final texture
SDL_Texture* newTexture = NULL;

//towards which direction will the hero walk?
int walkingDirection, walkingDirection_replica, walkingDirectionPrevious;

//images' file names:
char *gImageCurrent_name; //The variable image name to demonstrate


/****PROTOTYPES*************************************/
/****PROTOTYPES*************************************/
/****PROTOTYPES*************************************/

//Starts left SDL and creates window
bool init();

//*******************simply upload a map
bool simplyUploadAMap ();

//which image do you want to show ?
int chooseImage(char **gImageCurrent_name, size_t imageUseNumber_current, size_t imageUseNumber_total, int walkingDirection, int *walkingDirectionPrevious);

/***IMAGE********************************************/
bool loadMedia(const char *gImageCurrent_name);

/***free*************************/
void freeF(SDL_Window* gWindow, SDL_Surface* gScreenSurface, SDL_Surface* gImageCurrent);

/***QUIT MAIN LOOP****************/
bool quitF(SDL_Event e, bool *quit);

//Frees media and shuts down SDL
void closeF();


/****FUNCTIONS*************************************/
/****FUNCTIONS*************************************/
/****FUNCTIONS*************************************/

//*******************simply upload a map
bool simplyUploadAMap () {
	bool success = true;

	char *locationImageName;

	locationImageName = (char *) image_worldMap_name;

	//Load media
	if( !loadMedia( locationImageName ) ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to load media!\n" );
			success = false;
		}
	} else {

		//Color key image
		//SDL_SetColorKey( gImageCurrent, SDL_TRUE, SDL_MapRGB( gImageCurrent->format, 0xFF, 0xFF, 0xFF ) );

		//Get image dimensions
		mWidth = gImageCurrent->w;
		mHeight = gImageCurrent->h;
		if (DEBUG_LEVEL >= debug_test) {
			printf("image_worldMap_name: %s, mWidth: %d, mHeight: %d\n", image_worldMap_name, mWidth, mHeight);
		}


		//Apply the image
		SDL_BlitSurface( gImageCurrent, NULL, gScreenSurface, NULL );
		//Update the surface
		//SDL_UpdateWindowSurface( gWindow );

		//do you want to wait ?
		SDL_Delay( 0 );
		//**free*************************
		freeF(gWindow, gScreenSurface, gImageCurrent);
	}
	return success;
}

////*******************simply show that if a location is open on map
bool simplyUploadALocationAccessIndicator (  ) {
	bool success = true;

	char *locationImageName;



//int locationAccess [ LOCATION_ON_MAP_NUM_MAX ];
//int locationPosition_x [ LOCATION_ON_MAP_NUM_MAX ], locationPosition_y [ LOCATION_ON_MAP_NUM_MAX ];
//int locationCurrent = 0, locationMax = 2;

	if ( locationAccess [ locationCurrent ] == 1 ) {
		locationImageName = (char *) "2.1greenUnclicked.png";
	} else {
		locationImageName = (char *) "1.1redUnclicked.png";
	}

	//Load media
	if( !loadMedia( locationImageName ) ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to load media!\n" );
			success = false;
		}
	} else {

		//Color key image
		SDL_SetColorKey( gImageCurrent, SDL_TRUE, SDL_MapRGB( gImageCurrent->format, 0xFF, 0xFF, 0xFF ) );

		//Get image dimensions
		mWidth = gImageCurrent->w;
		mHeight = gImageCurrent->h;
		if (DEBUG_LEVEL >= debug_test) {
			printf("image_worldMap_name: %s, mWidth: %d, mHeight: %d\n", image_worldMap_name, mWidth, mHeight);
		}

		/*
				//change light indicator's location
				if ( locationCurrent == Gydanhil ) {
					locationPosition_x [ Gydanhil ] = Gydanhil_x; //place button on the location's x, y coordination
					locationPosition_y [ Gydanhil ] = Gydanhil_y;
				}
		*/
		//Apply the image
		SDL_Rect gImageCurrentPosition;
		gImageCurrentPosition.x = locationPosition_x [ locationCurrent ];
		gImageCurrentPosition.y = locationPosition_y [ locationCurrent ];

		//if (DEBUG_LEVEL >= debug_test) {
		printf("gImageCurrentPosition.x: %d, gImageCurrentPosition.y: %d\n", gImageCurrentPosition.x, gImageCurrentPosition.y);
		//}


		SDL_BlitSurface( gImageCurrent, NULL, gScreenSurface, &gImageCurrentPosition );

		//Update the surface
		//SDL_UpdateWindowSurface( gWindow );

		//do you want to wait ?
		//SDL_Delay( 0 );
		//**free*************************
		freeF(gWindow, gScreenSurface, gImageCurrent);
	}
	return success;
}

//which image do you want to show ?
int chooseImage(char **gImageCurrent_name, size_t imageUseNumber_current, size_t imageUseNumber_total, int walkingDirection, int *walkingDirectionPrevious) {

	////***movement variables**********************************
	//how fast does the hero walk (1000n/second)
	const int walkDelay = 150, runDelay = walkDelay/2;

	const char *gImageCurrent_name_pointerPrototype;

	//images' file names:

//BACK
	const char *image_hero1_back_01_name = "hero1_back_01.png";
	const char *image_hero1_back_02_name = "hero1_back_02.png";
	const char *image_hero1_back_03_name = "hero1_back_03.png";
	const char *image_hero1_back_04_name = "hero1_back_04.png";
//FRONT
	const char *image_hero1_front_01_name = "hero1_front_01.png";
	const char *image_hero1_front_02_name = "hero1_front_02.png";
	const char *image_hero1_front_03_name = "hero1_front_03.png";
	const char *image_hero1_front_04_name = "hero1_front_04.png";
//UP
	const char *image_hero1_left_01_name = "hero1_left_01.png";
	const char *image_hero1_left_02_name = "hero1_left_02.png";
	const char *image_hero1_left_03_name = "hero1_left_03.png";
	const char *image_hero1_left_04_name = "hero1_left_04.png";
//DOWN
	const char *image_hero1_right_01_name = "hero1_right_01.png";
	const char *image_hero1_right_02_name = "hero1_right_02.png";
	const char *image_hero1_right_03_name = "hero1_right_03.png";
	const char *image_hero1_right_04_name = "hero1_right_04.png";


	//continue the same direction?
	if ( *walkingDirectionPrevious == walkingDirection ) {
		walkingDirection = sameDirection;
	} else {
		*walkingDirectionPrevious = walkingDirection;
	}


	//which image do you want to show ?
	switch(walkingDirection) {
		case(map): {
			imageUseNumber_current = worldMap;
			break;
		}
		case(back): {
			imageUseNumber_current = hero1_back_01;
			break;
		}
		case(front): {
			imageUseNumber_current = hero1_front_01;
			break;
		}
		case(left): {
			imageUseNumber_current = hero1_left_01;
			break;
		}
		case(right): {
			imageUseNumber_current = hero1_right_01;
			break;
		}
		case(sameDirection): {
			break;
		}
		default: {
			if ( DEBUG_LEVEL >= debug_test ) {
				printf("Undefined walking direction\n");
			}
			break;
		}
	}

	//which image do you want to show ?
	switch ( imageUseNumber_current ) {
			//MAP
		case worldMap: {
			gImageCurrent_name_pointerPrototype = image_worldMap_name;
			//imageUseNumber_current++;
			break;
		}

		//BACK
		case hero1_back_01: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_back_01_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_back_02: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_back_02_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_back_03: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_back_03_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_back_04: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_back_04_name;
			imageUseNumber_current = hero1_back_01; //loop back to the first frame of animation
			break;
		}
		//FRONT
		case hero1_front_01: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_front_01_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_front_02: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_front_02_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_front_03: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_front_03_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_front_04: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_front_04_name;
			imageUseNumber_current = hero1_front_01; //loop front to the first frame of animation
			break;
		}
		//LEFT
		case hero1_left_01: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_left_01_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_left_02: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_left_02_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_left_03: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_left_03_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_left_04: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_left_04_name;
			imageUseNumber_current = hero1_left_01; //loop left to the first frame of animation
			break;
		}
		//RIGHT
		case hero1_right_01: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_right_01_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_right_02: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_right_02_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_right_03: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_right_03_name;
			imageUseNumber_current++;
			break;
		}
		case hero1_right_04: {
			SDL_Delay( walkDelay ); //delay before showing this image
			gImageCurrent_name_pointerPrototype = image_hero1_right_04_name;
			imageUseNumber_current = hero1_right_01; //loop right to the first frame of animation
			break;
		}

		default: {
			if ( DEBUG_LEVEL >= debug_test ) {
				printf("Undefined image number!\n");
			}
			break;
		}
	}


	*gImageCurrent_name = (char *)gImageCurrent_name_pointerPrototype;
	return imageUseNumber_current;
}

/****INITIAL*************************************/
bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		}
		success = false;
	} else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			if ( DEBUG_LEVEL >= debug_test ) {
				printf( "Warning: Linear texture filtering not enabled!" );
			}
		}

		//Create window
		gWindow = SDL_CreateWindow( "World Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			if ( DEBUG_LEVEL >= debug_test ) {
				printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			}
			success = false;
		} else {
			/***BMP ERA IMAGE*******************************/
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );

			/***ANIMATION ERA IMAGE*****************************************/
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL ) {
				if ( DEBUG_LEVEL >= debug_test ) {
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				}
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					if ( DEBUG_LEVEL >= debug_test ) {
						printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					}
					success = false;
				}
			}
		}
	}

	return success;
}

int getWidth() {
	return mWidth;
}

int getHeight() {
	return mHeight;
}


/***IMAGE********************************************/
bool loadMedia(const char *gImageCurrent_name) {
	//Loading success flag
	bool success = true;

	//Load splash image
	gImageCurrent = IMG_Load( gImageCurrent_name );
	if( gImageCurrent == NULL ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Unable to load image %s! SDL Error: %s\n", gImageCurrent_name, SDL_GetError() );
		}
		success = false;
	} else {
		bool success = true;
	}

	return success;
}


void setPosition( int x, int y ) {

	mButtonPosition.x = x;
	mButtonPosition.y = y;
}

int handleMouseEvent( SDL_Event* e ) {
	printf("entering handleEvent:\n");

	//Where's the cursor?
	int x, y;
	SDL_GetMouseState( &x, &y );


//	int locationPosition_x [ locationCurrent ], locationPosition_y [ locationCurrent ];
//	int locationCurrent = 0, locationMax = 2;
	//set the location indicator button
	mButtonPosition.x = locationPosition_x [ locationCurrent ];
	mButtonPosition.y = locationPosition_y [ locationCurrent ];


	printf("locationCurrent:%d, x: %d, y: %d; mButtonPosition.x: %d, mButtonPosition.y: %d\n", locationCurrent, x, y, mButtonPosition.x, mButtonPosition.y);


	//How is mouse being pressed?
	//if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ) {
	//printf("SDL_MOUSEMOTION: %d, SDL_MOUSEBUTTONDOWN: %d, SDL_MOUSEBUTTONUP: %d\n", SDL_MOUSEMOTION, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP );
	printf("e->type: %d\n", e->type );
	//}

	//Check if mouse is in button
	bool inside = true;

	//Mouse is left of the button
	if( x < mButtonPosition.x ) {
		inside = false;
	}
	//Mouse is right of the button
	else if( x > mButtonPosition.x + BUTTON_WIDTH ) {
		inside = false;
	}
	//Mouse above the button
	else if( y < mButtonPosition.y ) {
		inside = false;
	}
	//Mouse below the button
	else if( y > mButtonPosition.y + BUTTON_HEIGHT ) {
		inside = false;
	}

	//Mouse is outside button
	if( !inside ) {
		mCurrentState = BUTTON_SPRITE_MOUSE_OUT; //0
	}
	//Mouse is inside button
	else {
		//Set mouse over sprite
		switch( e->type ) {
			case SDL_MOUSEMOTION:
				mCurrentState = BUTTON_SPRITE_MOUSE_OVER_MOTION; //1
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentState = BUTTON_SPRITE_MOUSE_DOWN; //2
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentState = BUTTON_SPRITE_MOUSE_UP; //3
				break;
		}
	}

	return mCurrentState;
}










/***free*************************/
void freeF(SDL_Window* gWindow, SDL_Surface* gScreenSurface, SDL_Surface* gImageCurrent) {
	free(gImageCurrent);
	free(gScreenSurface);
	free(gWindow);
}

/*** QUIT the main loop **********************************************/
bool handleEventsInQueue(SDL_Event e, bool *quit) {

	//Handle events on queue
	while( SDL_PollEvent( &e ) != 0 ) {
		//User requests quit
		if( e.type == SDL_QUIT ) {
			*quit = true;
		}


		for( locationCurrent = 0; locationCurrent <= locationCap; locationCurrent++ ) { //try each unlocked scene
			handleMouseEvent( &e );
			//If the cursor is inside the button, how's the mouse being pressed?
			printf("mCurrentState: %d\n", mCurrentState);

			if ( mCurrentState == BUTTON_SPRITE_MOUSE_UP ) {
				targetAreaLocation = locationCurrent; //target Location chosen
				goto theUserHasPressedButton;
			}
		}
		//}
	}
theUserHasPressedButton:

	return *quit;
}

/****END******************************************************/
void closeF() {
	//Free loaded images
	//gSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

/***keep a character walking*********************************************/
void heroWalking (int *heroPosition_x, int *heroPosition_y, int *dx, int *dy, SDL_Event e, bool quit, size_t *imageUploadTurn ) {

	SDL_Rect gImageCurrentPosition;

	//towards what direction is the hero walking?
	//walkingDirection = map, walkingDirection_replica; //load the map first
	//walkingDirectionPrevious = walkingDirection;






	//*******************simply upload a map
	simplyUploadAMap ();
	//*******************button: can the locations be accessed?
	//int locationCurrent = 0, locationMax = 2;
	for ( locationCurrent = 0; locationCurrent <= locationMax; locationCurrent++ ) { //upload a button, locked or unlocked, onto the map
		simplyUploadALocationAccessIndicator (  );
	}

	//which image will be shown at this moment?
	imageUseNumber_current = chooseImage( &gImageCurrent_name, imageUseNumber_current, imageUseNumber_total, walkingDirection, &walkingDirectionPrevious );


	//Load media
	if( !loadMedia(gImageCurrent_name) ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to load media!\n" );
		}
	} else {

		//Color key image
		SDL_SetColorKey( gImageCurrent, SDL_TRUE, SDL_MapRGB( gImageCurrent->format, 0xFF, 0xFF, 0xFF ) );

		//Get image dimensions
		mWidth = gImageCurrent->w;
		mHeight = gImageCurrent->h;
		if (DEBUG_LEVEL >= debug_test) {
			printf("gImageCurrent_name: %s, mWidth: %d, mHeight: %d\n", gImageCurrent_name, mWidth, mHeight);
		}

		//change displacement
		*heroPosition_x += *dx;
		*heroPosition_y += *dy;

		//Apply the image
		gImageCurrentPosition.x = *heroPosition_x;
		gImageCurrentPosition.y = *heroPosition_y;

		if (DEBUG_LEVEL >= debug_test) {
			printf("gImageCurrentPosition.x: %d, gImageCurrentPosition.y: %d\n", gImageCurrentPosition.x, gImageCurrentPosition.y);
		}


		SDL_BlitSurface( gImageCurrent, NULL, gScreenSurface, &gImageCurrentPosition );
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );

		//do you want to wait ?
		SDL_Delay( 0 );
		/***free*************************/
		freeF(gWindow, gScreenSurface, gImageCurrent);
	}
}

//define where the locations are
void fillLocationCoordination() {

	locationPosition_x [ Gydanhil ] = Gydanhil_x; //location 0
	locationPosition_y [ Gydanhil ] = Gydanhil_y;

	locationPosition_x [ FroastoakVale ] = FroastoakVale_x; //location 1
	locationPosition_y [ FroastoakVale ] = FroastoakVale_y;

	locationPosition_x [ NessusRoad ] = NessusRoad_x; //location 2
	locationPosition_y [ NessusRoad ] = NessusRoad_y;

}

void fillLocationAccessibility() {
	locationAccess[ Gydanhil ] = 1; //location 0
	locationAccess[ FroastoakVale ] = 1; //location 1
	locationAccess[ NessusRoad ] = 0; //location 2

}

/****MAIN*************************************/
/****MAIN*************************************/
/****MAIN*************************************/
int main( int argc, char* args[] ) {

//which locations are open? //updated from battle section
	//locationAccess[ Gydanhil ] = 1;
	//locationAccess[ FroastoakVale ] = 1;
	//locationAccess[ NessusRoad ] = 0;

////***initialise map variables*************************************************


	//define where the locations are
	fillLocationCoordination();
	printf( "locationPosition_x [ Gydanhil ]: %d, locationPosition_y [ Gydanhil ]: %d\n", locationPosition_x [ Gydanhil ], locationPosition_y [ Gydanhil ] );
	printf( "locationPosition_x [ FroastoakVale ]: %d, locationPosition_y [ FroastoakVale ]: %d\n", locationPosition_x [ FroastoakVale ], locationPosition_y [ FroastoakVale ] );
	printf( "locationPosition_x [ NessusRoad ]: %d, locationPosition_y [ NessusRoad ]: %d\n", locationPosition_x [ NessusRoad ], locationPosition_y [ NessusRoad ] );

	//previous accessibility
	fillLocationAccessibility();
	printf( "locationAccess[ Gydanhil ]: %d, locationAccess[ FroastoakVale ]: %d, locationAccess[ NessusRoad ]: %d\n", locationAccess[ Gydanhil ], locationAccess[ FroastoakVale ], locationAccess[ NessusRoad ] );


	//the locations that can be accessed.
	if ( BattleWon == true ) {
		int a = locationCurrent+1;
		locationAccess [ a ] = 1; //unlock new location
		locationCap ++; //we are tautologous, for the time being...
	}

	//new accessibility
	//fillLocationAccessibility();
	printf( "locationAccess[ Gydanhil ]: %d, locationAccess[ FroastoakVale ]: %d, locationAccess[ NessusRoad ]: %d\n", locationAccess[ Gydanhil ], locationAccess[ FroastoakVale ], locationAccess[ NessusRoad ] );


	//hero's initial position
	heroPosition_x_Initial = locationPosition_x [ locationCurrent ] - 0.5 * heroImage_x;
	heroPosition_y_Initial = locationPosition_y [ locationCurrent ] - heroImage_y;

	//register where did the hero start
	sourceAreaLocation = locationCurrent;

////***initialise map variables*************************************************

	//*******show debug level*********************
	if ( DEBUG_LEVEL >= debug_test ) {
		printf("DEBUG_LEVEL: %d\n", DEBUG_LEVEL);
	}

	//Event handler
	SDL_Event e;


	//*******let hero walk on map*******************************
	//hero position
	int heroPosition_x = heroPosition_x_Initial, heroPosition_y = heroPosition_y_Initial;
	//how far does the hero walk by each step?
	int dx = walkPace_x, dy = walkPace_y;



	//Main loop flag
	bool quit = false;

	//count the turn for image to be uploaded
	size_t imageUploadTurn = 1; //0 is map, no longer used

	/****INITIAL*************************************/
	//Start left SDL and create window
	if( !init() ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to initialize!\n" );
		}
	} else {

		bool targetLocationReached = false;
		bool marchingTowardsTargetLocation = false;

		/***loop till quit*************************/
		while(  (!quit) && (!targetLocationReached) ) { //***LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP*******

			//is the user quitting or pressing mouse?
			handleEventsInQueue( e, &quit );

			//walk there, if button for a location is clicked
			if (  (  ( mCurrentState == BUTTON_SPRITE_MOUSE_UP ) && ( marchingTowardsTargetLocation == false )  ) || ( marchingTowardsTargetLocation == true )  ) {
				marchingTowardsTargetLocation = true; //marching

				if ( ( targetAreaLocation==1 )&&( sourceAreaLocation == targetAreaLocation - 1) ) {//if location 1's button is pressed, march from location 0
					targetAreaLocation = 1;
					//choose which image to upload
					switch ( imageUploadTurn  ) {
						case( 1 ):
						case( 10 ):
						case( 12 ):
						case( 15 ):
						case( 18 ):
						case( 23 ):
						case( 28 ): {
							walkingDirection = right;
							dx = walkPace_x;
							dy = 0;
							//heroPosition_x += 100;

							break;
						}
						case( 9999 ): {
							walkingDirection = left;
							dx = -walkPace_x;
							dy = 0;
							//heroPosition_x -= 100;

							break;
						}
						case( 7 ):
						case( 11 ):
						case( 13 ):
						case( 17 ):
						case( 22 ): {
							walkingDirection = front;
							dy = walkPace_y;
							dx = 0;
							//heroPosition_y += 100;
							break;
						}
						case( 27 ):
						case( 29 ): {
							walkingDirection = back;
							dy = -walkPace_y;
							dx = 0;
							//heroPosition_y -= 100;
							break;
						}
						case( 30 ): {//arrived target location
							dy = 0;
							dx = 0;
							targetLocationReached = true;
							marchingTowardsTargetLocation = false;
							sourceAreaLocation = targetAreaLocation; //we have arrived the new location
							printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
							break;
						}
					} //
					(imageUploadTurn) ++;
					/*
									//have we arrived? or on the way?
									(imageUploadTurn) ++;
									if ( imageUploadTurn >= 30 ) {
										//imageUploadTurn = 1;

									} else {
										marchingTowardsTargetLocation = true;
									}
					*/
					if ( DEBUG_LEVEL >= debug_test ) {
						printf("imageUploadTurn: %d\n", imageUploadTurn);
					}


					if ( DEBUG_LEVEL >= debug_test ) {
						printf( "dx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", dx, dy, walkPace_x, walkPace_y );
					}

					printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
				} else { //unlocked area
					marchingTowardsTargetLocation = false; //not marching
				}
			} else { //not walking
				walkingDirection = front;
				dy = 0;
				dx = 0;
			}
			//walking on map
			heroWalking ( &heroPosition_x, &heroPosition_y, &dx, &dy, e, quit, &imageUploadTurn);



		} //***LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP*******

		/****END******************************************************/
		//Free resources and close SDL
		freeF(gWindow, gScreenSurface, gImageCurrent);
		closeF();

	}

	return targetAreaLocation;
}



