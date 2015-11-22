enum boolean {false, true};
#include "SDL.h"
#define WIDTH 1080
#define HEIGHT 720
#define BUTTONS 3

/* This structure is for the player input buttons. the rectanlge is used to create the loction the buttons will appear. textures are a renderer are being used.*/
typedef struct button{
    SDL_Rect buttonPos;
    SDL_Texture *buttonTex[2];
    SDL_Surface *buttonSur[2];
}button;

int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos);
void createButtons(button buttonArray[], int count, SDL_Renderer *renderer);
int renderButtons(button buttonArray[], int count, SDL_Renderer *renderer);

int main(void)
{
	/* Window and renderer can be moved out of this function and put into a function where we first create a display */
    int i, j, attack;
    button buttonArray[BUTTONS];
    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;


    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    createButtons(buttonArray, BUTTONS, renderer);


    /*This function puts the buttons on the screen and captures which buttons you player   presses*/
    attack = renderButtons(buttonArray, BUTTONS, renderer);



    /* This part frees all surfaces and textures. A lot of this can be moved to a different function */
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
/* Checks for the left mouse button being clicked and checks where on the screen it was pressed, if over a button it toggles the button's state. */
int pressButton(SDL_Event* e, int choice, SDL_Rect buttonPos)
{
	int x, y;
    if(e->type == SDL_MOUSEBUTTONDOWN){
        SDL_GetMouseState(&x, &y);
		if( x > buttonPos.x && x < buttonPos.x + buttonPos.w &&
            y > buttonPos.y &&  y < buttonPos.y + buttonPos.h){
			return 1 - choice;
		}
    }
    return choice;
}

void createButtons(button buttonArray[], int count, SDL_Renderer *renderer)
{
    int w = 100, h = 100, x = 250, y = 550, i;
    FILE* buttonFiles;
    char offFile[15], onFile[15];
    // Sets the positions of the buttons 
    buttonFiles = fopen("buttonFiles.txt", "r");
	for(i = 0; i < count; i++){
		buttonArray[i].buttonPos.w = w;
		buttonArray[i].buttonPos.h = h;
		buttonArray[i].buttonPos.y = y;
        if(i == count - 1){
    		buttonArray[i].buttonPos.x = x + (w + 50) * i;
        }
        else{
    		buttonArray[i].buttonPos.x = x + (w + 10) * i;
        }
        // Buttons images are read from a file of files
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

int renderButtons(button buttonArray[], int count, SDL_Renderer *renderer)
{
    int i, run = 1, attack = 0;
    int choice[BUTTONS] = {0};
    SDL_Event event;
    while(run){
        if (SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                run = 0;
            }
            for(i = 0; i < count; i++){
                choice[i] = pressButton(&event, choice[i], buttonArray[i].buttonPos);
            }
            if(choice[count - 1] == 1){
                run = 0;
            }
        }
        //Renders the button the the user has selected
        SDL_RenderClear(renderer);
        for(i = 0; i < count; i++){
            SDL_RenderCopy(renderer, buttonArray[i].buttonTex[choice[i]], NULL, 
                &buttonArray[i].buttonPos);
        }
        SDL_RenderPresent(renderer);
    }
    for(i = 0; i < count -1; i++){
        attack += choice[i] * 10 ^ i;
    }
    return attack;
}
