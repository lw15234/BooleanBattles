enum boolean {false, true};
#include "SDL.h"
#define WIDTH 1080
#define HEIGHT 720

int pressbutton(SDL_Event* e, int choice, SDL_Rect buttonPos);

	SDL_Event event;
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSurface[2];

int main(void)
{
    int i;
    int run = 1;
    int choice = false;
    
    SDL_Rect buttonPos;
    buttonPos.w = 100;
    buttonPos.h = 100;
    buttonPos.x = 250;
    buttonPos.y = 550;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    //creation of the two buttons
    buttonSurface[0] = SDL_LoadBMP("onfire.bmp");
    buttonTex[0] = SDL_CreateTextureFromSurface(renderer, buttonSurface[0]);

    buttonSurface[1] = SDL_LoadBMP("fire.bmp");
    buttonTex[1] = SDL_CreateTextureFromSurface(renderer, buttonSurface[1]);

    while(run){
        if (SDL_PollEvent(&event)){
            //Exits the loop if the user closes the window
            if(event.type == SDL_QUIT){
                run = 0;
            }
            choice = pressbutton(&event, choice, buttonPos);
        }
        //Renders the button the the user has selected
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, buttonTex[choice], NULL, &buttonPos);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    for(i = 0; i < 2; i++){
        SDL_DestroyTexture(buttonTex[i]);
        SDL_FreeSurface(buttonSurface[i]);
    }
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

int pressbutton(SDL_Event* e, int choice, SDL_Rect buttonPos)
{
	int x, y;
    int inside;
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP ){
        SDL_GetMouseState(&x, &y);
        inside = true;
		if( x < buttonPos.x )
		{
			inside = false;
		}
		else if( x > buttonPos.x + buttonPos.w )
		{
			inside = false;
		}
		else if( y < buttonPos.y )
		{
			inside = false;
		}
		else if( y > buttonPos.y + buttonPos.h)
		{
			inside = false;
		}

        if(inside == true)
        {
            if(e->type == SDL_MOUSEBUTTONDOWN){
                return 1 - choice;
            }
        }
    }
    return choice;
}

/* Next task is to add additional buttons
- make the buttons a function
- return from the function an integer number representing the player choice
