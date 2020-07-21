//将SDL函数和数据类型包含进来
#include "SDL.h"

#pragma comment(lib, "SDL2.lib")

int main( int argc, char* args[] )
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "SDL video init failed: %s\n", SDL_GetError());
    return 1;
}

// SDL_Surface *screenSurface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

window = SDL_CreateWindow("Sphere Rendering", 
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

if (window == NULL) {
    fprintf(stderr, "Window could not be created: %s\n", SDL_GetError());
    return 1;
}

screenSurface = SDL_GetWindowSurface(window);

if (!screenSurface) {
    fprintf(stderr, "Screen surface could not be created: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
}

// SDL_WM_SetCaption("Sphere Rendering", NULL);
 
    return 0;
}