#include "SDL.h"
#include <iostream>

int main(int argc, char *argv[]) {

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout<<"SDL2 couldn't initialize "<<SDL_GetError()<<std::endl;
        return 0;
    }

    auto window = SDL_CreateWindow(
        "TestSDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0
    );

    if(window == NULL) {
        std::cout<<"SDL2 couldn't create a window "<<SDL_GetError()<<std::endl;
        return 0;
    }

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)255, (Uint8)0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //Wait two seconds
    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}