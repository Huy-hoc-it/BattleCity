#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "game.h"

using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Battle city";

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    game(renderer, texture, SCREEN_WIDTH, SCREEN_HEIGHT);

    waitUntilKeyPressed();
    quitSDL(window, renderer, texture);
    return 0;
}
