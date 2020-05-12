//
// Created by nitishingde on 11/04/20.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

TEST_CASE("Initialization of SDL2, SDL2_ttf, SDL2_image", "[init]") {

    REQUIRE(0 <= SDL_Init(SDL_INIT_VIDEO));
    CHECK(0 <= IMG_Init(IMG_InitFlags::IMG_INIT_PNG));
    CHECK(0 <= TTF_Init());

    auto window = SDL_CreateWindow(
            "TestSDL2",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            0
    );

    CHECK(window != NULL);

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, (Uint8)255, (Uint8)255, (Uint8)0, 128);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //Wait two seconds
    SDL_Delay(1000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
