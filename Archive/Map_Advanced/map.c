/*********************************************
1. import and export values:
This program needs to know the location where the last battle was fought, and how many levels have been unlocked.
It exports the location number that the player has reached, before entering the battle.

The buttons on the map requires knowledge about whether a battlefield is unlocked, for every available battlefield.
It requires to import 3 int arrays:

2. maintenance:
This map is fully functional for the first 3 levels, and shows map for 10 levels.

More levels are about to be added, and reverse movement can be implemented:
//algorithms to be implemented:
[a. path coding notes:]

//update: a realistic movement should also be a bit random
//fully automatic path finding if necessary

[b. reverse movement notes:]
for a path from i to m, with n steps,
to go from i to m:
at step a, one goes direction d, with velocity v;
to go from m to i:
at step (n-a), one goes direction -d, with velocity -v;

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
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
//#include <SDL_image.h>

#define LOCATION_ON_MAP_NUM_MAX 100

//**import values******************************
int locationCurrent = 0, locationCap = 9;


//**export values******************************
int targetAreaLocation;


/***SELECT FROM OPTIONS*****************************************/
/***SELECT FROM OPTIONS*****************************************/
/***SELECT FROM OPTIONS*****************************************/

//debug?
enum {debug_no, debug_test, debug_total};
const int DEBUG_LEVEL = debug_test;

//Screen dimension constants
enum {mapX = 1080, mapY = 720};
const int SCREEN_WIDTH = mapX;
const int SCREEN_HEIGHT = mapY;

enum { heroImage_x = 32, heroImage_y = 48 };

//map locations
const int locationMax = 9;

int locationPosition_x [ LOCATION_ON_MAP_NUM_MAX ], locationPosition_y [ LOCATION_ON_MAP_NUM_MAX ]; //what are the battlefields' coordinations on the map?
int locationAccess [ LOCATION_ON_MAP_NUM_MAX ]; //which battlefields can the hero now access?

enum {screenBorderLength_left=46, screenBorderLength_right=43, screenBorderLength_up=45, screenBorderLength_down=38};
//typedef enum location_t {Gydanhil_x=337, Gydanhil_y=323, //location 0
//                         FroastoakVale_x = 432, FroastoakVale_y = 346, //location 1
//                         NessusRoad_x = 505, NessusRoad_y = 378 //location 2
//                        } location_t;


typedef enum location_t {location0x = 38, location0y = 50,
                         location1x = 279, location1y = 50,
                         location2x = 520, location2y = 51,
                         location3x = 776, location3y = 13,
                         location4x = 849, location4y = 184,
                         location5x = 777, location5y = 366,
                         location6x = 724, location6y = 503,
                         location7x = 538, location7y = 549,
                         location8x = 315, location8y = 503,
                         location9x = 83, location9y = 579
                        } location_t;

enum {location0,
      location1,
      location2,
      location3,
      location4,
      location5,
      location6,
      location7,
      location8,
      location9
     };



int sourceAreaLocation; //int targetAreaLocation;

int d_sourceAreaLocation_targetAreaLocation = 0; //difference between sourceAreaLocation and targetAreaLocation
int targetAreaLocationReplica; //save the final targetAreaLocation, while travel for the short term location

bool targetLocationReached = false;
bool marchingTowardsTargetLocation = false;
//towards what direction is the hero walking?
enum {map, back, front, left, right, sameDirection};

//SELECT IMAGE NUMBER
enum {worldMap, //0
      hero1_back_01, hero1_back_02, hero1_back_03, hero1_back_04, //1-4
      hero1_front_01, hero1_front_02, hero1_front_03, hero1_front_04, //5-8
      hero1_left_01, hero1_left_02, hero1_left_03, hero1_left_04, //9-12
      hero1_right_01, hero1_right_02, hero1_right_03, hero1_right_04 //13-16
     };

int imageUseNumber_current=worldMap, imageUseNumber_total=hero1_front_04;

//***movement variables***************************************************************
//hero's initial position
int heroPosition_x_Initial, heroPosition_y_Initial;
//how far does the hero walk by each step?
enum { walkPace_x = 5, walkPace_y = 5 };

//MAP
char *image_worldMap_name = "Map_level_1.bmp";

//****Mouse********************************************************
//Button constants
const int BUTTON_WIDTH = 80;
const int BUTTON_HEIGHT = 80;
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
int chooseImage(char **gImageCurrent_name, int imageUseNumber_current, /*int imageUseNumber_total, */int walkingDirection, int *walkingDirectionPrevious);

//***IMAGE********************************************
bool loadMedia(const char *gImageCurrent_name);

//***free*************************
void freeF(SDL_Window* gWindow, SDL_Surface* gScreenSurface, SDL_Surface* gImageCurrent);

//***QUIT MAIN LOOP****************
bool quitF(SDL_Event e, bool *quit);

//Frees media and shuts down SDL
void closeF();


/****FUNCTIONS*************************************/
/****FUNCTIONS*************************************/
/****FUNCTIONS*************************************/

//*******************simply upload a map
bool simplyUploadAMap () {
	bool success = true;

	if ( locationCap == 0 ) {
		image_worldMap_name = "Map_level_1.bmp";
	} else if ( locationCap == 1 ) {
		image_worldMap_name = "Map_level_2.bmp";
	} else if ( locationCap == 2 ) {
		image_worldMap_name = "Map_level_3.bmp";
	} else if ( locationCap == 3 ) {
		image_worldMap_name = "Map_level_4.bmp";
	} else if ( locationCap == 4 ) {
		image_worldMap_name = "Map_level_5.bmp";
	} else if ( locationCap == 5 ) {
		image_worldMap_name = "Map_level_6.bmp";
	} else if ( locationCap == 6 ) {
		image_worldMap_name = "Map_level_7.bmp";
	} else if ( locationCap == 7 ) {
		image_worldMap_name = "Map_level_8.bmp";
	} else if ( locationCap == 8 ) {
		image_worldMap_name = "Map_level_9.bmp";
	} else if ( locationCap == 9 ) {
		image_worldMap_name = "Map_level_10.bmp";
	}
printf("in simplyUploadAMap: 11\n");

	//Load media
	if( !loadMedia( image_worldMap_name ) ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to load media!\n" );
			success = false;
		}
	} else {
printf("in simplyUploadAMap: 12\n");
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
		SDL_Delay( 1000 );
		//**free*************************
		freeF(gWindow, gScreenSurface, gImageCurrent);
	}
printf("in simplyUploadAMap: 19\n");
	return success;
}


//which image do you want to show ?
int chooseImage(char **gImageCurrent_name, int imageUseNumber_current,/* int imageUseNumber_total, */int walkingDirection, int *walkingDirectionPrevious) {


// imageUseNumber_total = 0; // unused variable 
	////***movement variables**********************************
	//how fast does the hero walk (1000n/second)
	const int walkDelay = 75; /*const int runDelay = walkDelay/2;*/

	const char *gImageCurrent_name_pointerPrototype = NULL;

	//images' file names:

//BACK
	const char *image_hero1_back_01_name = "hero1_back_01.bmp";
	const char *image_hero1_back_02_name = "hero1_back_02.bmp";
	const char *image_hero1_back_03_name = "hero1_back_03.bmp";
	const char *image_hero1_back_04_name = "hero1_back_04.bmp";
//FRONT
	const char *image_hero1_front_01_name = "hero1_front_01.bmp";
	const char *image_hero1_front_02_name = "hero1_front_02.bmp";
	const char *image_hero1_front_03_name = "hero1_front_03.bmp";
	const char *image_hero1_front_04_name = "hero1_front_04.bmp";
//UP
	const char *image_hero1_left_01_name = "hero1_left_01.bmp";
	const char *image_hero1_left_02_name = "hero1_left_02.bmp";
	const char *image_hero1_left_03_name = "hero1_left_03.bmp";
	const char *image_hero1_left_04_name = "hero1_left_04.bmp";
//DOWN
	const char *image_hero1_right_01_name = "hero1_right_01.bmp";
	const char *image_hero1_right_02_name = "hero1_right_02.bmp";
	const char *image_hero1_right_03_name = "hero1_right_03.bmp";
	const char *image_hero1_right_04_name = "hero1_right_04.bmp";


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
			//gScreenSurface = SDL_GetWindowSurface( gWindow );

			/***ANIMATION ERA IMAGE*****************************************/
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC */ );
			if( gRenderer == NULL ) {
				if ( DEBUG_LEVEL >= debug_test ) {
					printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				}
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
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
printf("in loadMedia: 21\n");
	//Loading success flag
	bool success = true;

	//Load splash image
	gImageCurrent = SDL_LoadBMP( gImageCurrent_name );
	if( gImageCurrent == NULL ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Unable to load image %s! SDL Error: %s\n", gImageCurrent_name, SDL_GetError() );
		}
		success = false;
	} else {
		success = true;
	}
printf("in loadMedia: 29\n");
	return success;

}


void setPosition( int x, int y ) {

	mButtonPosition.x = x;
	mButtonPosition.y = y;
}

int handleMouseEvent( SDL_Event* e ) {
	if ( DEBUG_LEVEL >= debug_test ) {
		printf("entering handleEvent:\n");
	}

	//Where's the cursor?
	int x, y;
	SDL_GetMouseState( &x, &y );


	mButtonPosition.x = locationPosition_x [ locationCurrent ];
	mButtonPosition.y = locationPosition_y [ locationCurrent ];

	if ( DEBUG_LEVEL >= debug_test ) {
		printf("locationCurrent:%d, x: %d, y: %d; mButtonPosition.x: %d, mButtonPosition.y: %d\n", locationCurrent, x, y, mButtonPosition.x, mButtonPosition.y);
	}


	if ( DEBUG_LEVEL >= debug_test ) {
		printf("e->type: %d\n", e->type );
	}

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
			if ( DEBUG_LEVEL >= debug_test ) {
				printf("mCurrentState: %d\n", mCurrentState);
			}

			if ( mCurrentState == BUTTON_SPRITE_MOUSE_UP ) {
				targetAreaLocation = locationCurrent; //target Location chosen
				targetAreaLocationReplica = targetAreaLocation; //note down the final goal

				goto theUserHasPressedButton;
			}
		}
		//}
	}
theUserHasPressedButton:
	printf("in handleEventsInQueue: targetAreaLocation: %d\n", targetAreaLocation);

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
	//IMG_Quit();
	SDL_Quit();
}

/***keep a character walking*********************************************/
void heroWalking (int *heroPosition_x, int *heroPosition_y, int *dx, int *dy/*, SDL_Event e, bool quit, int *imageUploadTurn*/ ) {
printf("in heroWalking: 41\n");
	SDL_Rect gImageCurrentPosition;

	//*******************simply upload a map
	simplyUploadAMap ();
	//*******************button: can the locations be accessed?

	//which image will be shown at this moment?
	imageUseNumber_current = chooseImage( &gImageCurrent_name, imageUseNumber_current, /*imageUseNumber_total,*/ walkingDirection, &walkingDirectionPrevious );


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

printf("in heroWalking: 47\n");
		SDL_BlitSurface( gImageCurrent, NULL, gScreenSurface, &gImageCurrentPosition );
		//Update the surface
		SDL_UpdateWindowSurface( gWindow );
printf("in heroWalking: 48\n");
		//do you want to wait ?
		SDL_Delay( 0 );
		/***free*************************/
		freeF(gWindow, gScreenSurface, gImageCurrent);
	}
}

//define where the locations are
void fillLocationCoordination() {

	locationPosition_x [ location0 ] = location0x ; //location 0
	locationPosition_y [ location0 ] = location0y ;

	locationPosition_x [ location1 ] = location1x ; //location 1
	locationPosition_y [ location1 ] = location1y ;

	locationPosition_x [ location2 ] = location2x ; //location 2
	locationPosition_y [ location2 ] = location2y ;

	locationPosition_x [ location3 ] = location3x ; //location 3
	locationPosition_y [ location3 ] = location3y ;

	locationPosition_x [ location4 ] = location4x ; //location 4
	locationPosition_y [ location4 ] = location4y ;

	locationPosition_x [ location5 ] = location5x ; //location 5
	locationPosition_y [ location5 ] = location5y ;

	locationPosition_x [ location6 ] = location6x ; //location 6
	locationPosition_y [ location6 ] = location6y ;

	locationPosition_x [ location7 ] = location7x ; //location 7
	locationPosition_y [ location7 ] = location7y ;

	locationPosition_x [ location8 ] = location8x ; //location 8
	locationPosition_y [ location8 ] = location8y ;

	locationPosition_x [ location9 ] = location9x ; //location 9
	locationPosition_y [ location9 ] = location9y ;

}

void fillLocationAccessibility() {

	int arrayCounter;

	for ( arrayCounter=0; arrayCounter<=locationCap; arrayCounter++ )
		locationAccess[ arrayCounter ] = 1;

}

//*********************define directions
//what does it mean by stand still, looking at us?
void standStillFaceFront( int *dx, int *dy ) {
	walkingDirection = front;

	*dy = 0;
	*dx = 0;
}
//what does it mean by stand still, back against us?
void standStillFaceBack( int *dx, int *dy ) {
	walkingDirection = back;

	*dy = 0;
	*dx = 0;
}

//what does it mean by going right?
void goRight( int *dx, int *dy ) {
	walkingDirection = right;

	*dx = walkPace_x;
	*dy = 0;
}
//what does it mean by going left?
void goLeft( int *dx, int *dy ) {
	walkingDirection = left;

	*dx = -walkPace_x;
	*dy = 0;
}
//what does it mean by moving towards us?
void goFront( int *dx, int *dy ) {
	walkingDirection = front;

	*dy = walkPace_y;
	*dx = 0;
}
//what does it mean by moving away from us?
void goBack( int *dx, int *dy ) {
	walkingDirection = back;

	*dy = -walkPace_y;
	*dx = 0;
}


//**********************code path from one level to another

//march from location 0 - 1
void marchFromLocation0To1 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;

	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( 1 ): {

			goRight( &dx, &dy );

			break;
		}
		case( INT_MAX - 1 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goFront( &dx, &dy );

			break;
		}
		case( ( location1x - location0x  )/walkPace_x ): {

			goBack( &dx, &dy );

			break;
		}
		case(   (  ( location1x - location0x  )/walkPace_x  ) + 1   ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;

}

//march from location 1 - 2
void marchFromLocation1To2 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;

	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( 1 ): {

			goRight( &dx, &dy );

			break;
		}
		case( INT_MAX - 1 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goFront( &dx, &dy );

			break;
		}
		case( ( location2x - location1x  )/walkPace_x ): {

			goBack( &dx, &dy );

			break;
		}
		case(  ( ( location2x - location1x  )/walkPace_x ) + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

//march from location 2 - 3
void marchFromLocation2To3 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;

//x:right, y:back
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( 1 ):
		case( 18 ):
		case( 35 ):
		case( 51 ):


		{

			goRight( &dx, &dy );

			break;
		}
		case( INT_MAX - 1 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goFront( &dx, &dy );

			break;
		}
		case( 16 ):
		case( 33 ):
		case( 49 ):
{

			goBack( &dx, &dy );

			break;
		}
		case(  58 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}


//march from location 3 - 4
void marchFromLocation3To4 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;

	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( 3 ):
			//case( 6 ):
			//case( 10 ):

		case( 13 ):
			//case( 17 ):
			//case( 20 ):

		case( 24 ):
			//case( 27 ):
			//case( 30 ):

		case( 34 ):
			//case( 37 ):
			//case( 41 ):

		case( 44 ):
			//case( 48 ):
		{

			goRight( &dx, &dy );

			break;
		}
		case( INT_MAX - 1 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 4+2 ):
			//case( 7 ):
			//case( 11 ):

		case( 14+2 ):
			//case( 18 ):
			//case( 21 ):

		case( 25+2 ):
			//case( 28 ):
			//case( 31 ):

		case( 35+2 ):
			//case( 38 ):
			//case( 42 ):

		case( 45+2 ): {

			goFront( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goBack( &dx, &dy );

			break;
		}
		case(  48 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

//march from location 4 - 5
void marchFromLocation4To5 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;
//x:left;y:front
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( INT_MAX - 1 ): {

			goRight( &dx, &dy );

			break;
		}

		case( 14 ):
		case( 28 ):
		case( 42 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 18 ):
		case( 32 ):
		case( 46 ): {

			goFront( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goBack( &dx, &dy );

			break;
		}
		case(  48 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}


//march from location 5 - 6
void marchFromLocation5To6 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;
//x:left;y:front
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( INT_MAX - 1 ): {

			goRight( &dx, &dy );

			break;
		}

		case( 11 ):
		case( 22 ):
		case( 33 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 14 ):
		case( 25 ):
		case( 36 ): {

			goFront( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goBack( &dx, &dy );

			break;
		}
		case(  37 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

//march from location 6 - 7
void marchFromLocation6To7 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;
//x:left;y:front
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( INT_MAX - 1 ): {

			goRight( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 18 ):
		case( 33 ): {

			goLeft( &dx, &dy );

			break;
		}

		case( 15 ):
		case( 30 ):
		case( 46 ): {

			goFront( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goBack( &dx, &dy );

			break;
		}
		case(  46 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

//march from location 7 - 8
void marchFromLocation7To8 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;
//x:left;y:back
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( INT_MAX - 1 ): {

			goRight( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 20 ):
		case( 38 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goFront( &dx, &dy );

			break;
		}
		case( 17 ):
		case( 35 ):
		case( 53 ): {

			goBack( &dx, &dy );

			break;
		}
		case(  53 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

//march from location 8 - 9
void marchFromLocation8To9 ( int *imageUploadTurn_original, int *dx_original, int *dy_original, bool *targetLocationReached_original, bool *marchingTowardsTargetLocation_original  ) {

	int imageUploadTurn = *imageUploadTurn_original; //manipulate pointers
	int dx = *dx_original;
	int dy = *dy_original;
	bool targetLocationReached = *targetLocationReached_original;
	bool marchingTowardsTargetLocation = *marchingTowardsTargetLocation_original;
//x:left;y:front
	//choose which image to upload
	switch ( imageUploadTurn  ) {
		case( INT_MAX - 1 ): {

			goRight( &dx, &dy );

			break;
		}
		case( 1 ):
		case( 25 ):
		case( 45 ): {

			goLeft( &dx, &dy );

			break;
		}
		case( 20 ):
		case( 40 ):
		case( 61 ): {

			goFront( &dx, &dy );

			break;
		}
		case( INT_MAX ): {

			goBack( &dx, &dy );

			break;
		}
		case(  61 + 1  ): {//arrived target location

			//stand still, back against us(look at the (temporary) location)
			standStillFaceBack( &dx, &dy );

			printf("d_sourceAreaLocation_targetAreaLocation: %d\n", d_sourceAreaLocation_targetAreaLocation);
			//d_sourceAreaLocation_targetAreaLocation --;
			if ( d_sourceAreaLocation_targetAreaLocation >=1 ) {

				sourceAreaLocation = targetAreaLocation; //arriving the new location
				targetAreaLocation = targetAreaLocationReplica; //recall the final goal

				targetLocationReached = false; //don't quit

				imageUploadTurn = 0; //restore image upload turn

				marchingTowardsTargetLocation = true;

			} else {
				targetLocationReached = true;
				marchingTowardsTargetLocation = false;

				locationCurrent = sourceAreaLocation = targetAreaLocation; //we have arrived the new location
				printf("sourceAreaLocation: %d\n\n", sourceAreaLocation);
			}
			break;
		}
	} //
	(imageUploadTurn) ++;



	*imageUploadTurn_original = imageUploadTurn  ; //restore original variables
	*dx_original = dx;
	*dy_original = dy;
	*targetLocationReached_original = targetLocationReached;
	*marchingTowardsTargetLocation_original = marchingTowardsTargetLocation;
}

/****MAIN*************************************/
/****MAIN*************************************/
/****MAIN*************************************/
int main( void ) {


////***initialise map variables*************************************************


	//define where the locations are
	fillLocationCoordination();
	if ( DEBUG_LEVEL >= debug_test ) {
		printf( "locationPosition_x [ location0 ]: %d, locationPosition_y [ location0 ]: %d\n", locationPosition_x [ location0 ], locationPosition_y [ location0 ] );
		printf( "locationPosition_x [ location1 ]: %d, locationPosition_y [ location1 ]: %d\n", locationPosition_x [ location1 ], locationPosition_y [ location1 ] );
		printf( "locationPosition_x [ location2 ]: %d, locationPosition_y [ location2 ]: %d\n", locationPosition_x [ location2 ], locationPosition_y [ location2 ] );
	}

	//previous accessibility
	fillLocationAccessibility();
	if ( DEBUG_LEVEL >= debug_test ) {
		printf( "locationAccess[ location0 ]: %d, locationAccess[ location1 ]: %d, locationAccess[ location2 ]: %d\n", locationAccess[ location0 ], locationAccess[ location1 ], locationAccess[ location2 ] );
	}




	//hero's initial position
	heroPosition_x_Initial = locationPosition_x [ locationCurrent ] - 0.5 * heroImage_x + 0.5 * BUTTON_WIDTH;
	heroPosition_y_Initial = locationPosition_y [ locationCurrent ] - heroImage_y + BUTTON_HEIGHT - 10;

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
	int imageUploadTurn = 1; //0 is map, no longer used

	/****INITIAL*************************************/
	//Start left SDL and create window
	if( !init() ) {
		if ( DEBUG_LEVEL >= debug_test ) {
			printf( "Failed to initialize!\n" );
		}
	} else {

		targetLocationReached = false;
		marchingTowardsTargetLocation = false;
printf("in main: 030\n");
		/***loop till quit*************************/
		while(  ( quit==false ) && ( targetLocationReached==false )  ) { //***LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP*******
printf("in main: 040\n");

			//is the user quitting or pressing mouse?
			handleEventsInQueue( e, &quit );

			//what's the current difference between start and end location?
			d_sourceAreaLocation_targetAreaLocation = targetAreaLocationReplica - sourceAreaLocation;
			printf("sourceAreaLocation: %d, targetAreaLocation: %d, targetAreaLocationReplica: %d, d_sourceAreaLocation_targetAreaLocation%d\n", sourceAreaLocation, targetAreaLocation, targetAreaLocationReplica, d_sourceAreaLocation_targetAreaLocation);

printf("in main: 060\n");
			//walk there, if button for a location is clicked
			if (  (  ( mCurrentState == BUTTON_SPRITE_MOUSE_UP ) && ( marchingTowardsTargetLocation == false )  ) || ( marchingTowardsTargetLocation == true )  ) {
				marchingTowardsTargetLocation = true; //marching

				if ( sourceAreaLocation == targetAreaLocation ) { //if reenter current battlefield
					printf("targetAreaLocation: %d\n", targetAreaLocation);
					return targetAreaLocation;



				} else if ( sourceAreaLocation <= targetAreaLocation - 1) { //if from early battlefield to later battlefield


					if ( d_sourceAreaLocation_targetAreaLocation >= 2 ) { // if the final goal isn't the next battle
						targetAreaLocation = sourceAreaLocation + 1; //set a short term goal

					}

					//march from location 0 - 1
					if (  ( targetAreaLocation == 1 )  ) {
						marchFromLocation0To1 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 1 - 2
					else if (  ( targetAreaLocation == 2 )  ) {
						marchFromLocation1To2 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 2 - 3
					else if (  ( targetAreaLocation == 3 )  ) {
						marchFromLocation2To3 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 3 - 4
					else if (  ( targetAreaLocation == 4 )  ) {
						marchFromLocation3To4 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 4 - 5
					else if (  ( targetAreaLocation == 5 )  ) {
						marchFromLocation4To5 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 5 - 6
					else if (  ( targetAreaLocation == 6 )  ) {
						marchFromLocation5To6 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 6 - 7
					else if (  ( targetAreaLocation == 7 )  ) {
						marchFromLocation6To7 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 7 - 8
					else if (  ( targetAreaLocation == 8 )  ) {
						marchFromLocation7To8 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}
					//march from location 8 - 9
					else if (  ( targetAreaLocation == 9 )  ) {
						marchFromLocation8To9 ( &imageUploadTurn, &dx, &dy, &targetLocationReached, &marchingTowardsTargetLocation );

						if ( DEBUG_LEVEL >= debug_test ) {
							printf("imageUploadTurn: %d\ndx: %d, dy: %d; walkPace_x: %d, walkPace_y: %d\n", imageUploadTurn, dx, dy, walkPace_x, walkPace_y);
						}
						printf("targetLocationReached: %d, marchingTowardsTargetLocation: %d\n", targetLocationReached, marchingTowardsTargetLocation);
					}


				} else { //unlocked area
					marchingTowardsTargetLocation = false; //not marching
				}
			} else { //not walking




				//stand still, looking at us
				standStillFaceFront( &dx, &dy );

			}
			//walking on map
			heroWalking ( &heroPosition_x, &heroPosition_y, &dx, &dy/*, e, quit, &imageUploadTurn*/ );



		} //***LOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP*******
printf("in main: 080\n");
		/****END******************************************************/
		//Free resources and close SDL
		freeF(gWindow, gScreenSurface, gImageCurrent);
		closeF();

	}
	//printf("targetLocationReached: %s\n"), targetLocationReached ? "true" : "false";
	printf("targetAreaLocation: %d\n", targetAreaLocation);

	return targetAreaLocation;
}



