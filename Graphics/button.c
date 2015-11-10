enum boolean {false, true};
#include "SDL.h"
#define WIDTH 1080
#define HEIGHT 720
#define BUTTONS 3

typedef struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
}button;

int pressbutton(SDL_Event* e, int choice, SDL_Rect buttonPos);
void createButtons(button buttonArray[], int count, SDL_Renderer *renderer);

int main(void)
{
    int i, j;
    int run = 1;
    int choice[BUTTONS] = {0};    
    button buttonArray[BUTTONS];

    SDL_Event event;
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    win = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    createButtons(buttonArray, BUTTONS, renderer);

    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
            }
            for(i = 0; i < BUTTONS; i++){
                choice[i] = pressbutton(&event, choice[i], buttonArray[i].buttonPos);
            }
            
        }
        //Renders the button the the user has selected
        SDL_RenderClear(renderer);
        for(i = 0; i < BUTTONS; i++){
            SDL_RenderCopy(renderer, buttonArray[i].buttonTex[choice[i]], NULL, 
                &buttonArray[i].buttonPos);
        }
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    for(i = 0; i < 3; i++){
        for(j = 0; j < 2; j++){
            SDL_DestroyTexture(buttonArray[i].buttonTex[j]);
            SDL_FreeSurface(buttonArray[i].buttonSur[j]);
        }
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

void createButtons(button buttonArray[], int count, SDL_Renderer *renderer)
{
    int w = 100, h = 100, x = 250, y = 550, i;
    FILE* buttonFiles;
    char offFile[15], onFile[15];



    buttonFiles = fopen("buttonFiles.txt", "r");
	for(i = 0; i < count; i++){
		buttonArray[i].buttonPos.w = w;
		buttonArray[i].buttonPos.h = h;
		buttonArray[i].buttonPos.x = x + (w + 10) * i;
		buttonArray[i].buttonPos.y = y;

        if(fscanf(buttonFiles, "%s %s", offFile, onFile) == 2){
            printf("%s %s\n",offFile, onFile);
            buttonArray[i].buttonSur[0] = SDL_LoadBMP(offFile);
            buttonArray[i].buttonSur[1] = SDL_LoadBMP(onFile);
            buttonArray[i].buttonTex[0] = 
                SDL_CreateTextureFromSurface(renderer, buttonArray[i].buttonSur[0]);
            buttonArray[i].buttonTex[1] = 
                SDL_CreateTextureFromSurface(renderer, buttonArray[i].buttonSur[1]);
        }
        else{
            printf("Could not find files\n");
            exit(1);
        }
	}
    fclose(buttonFiles);
}

