#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SDL_utils.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Battle city";
const int BULLET_SPEED = 8;




int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);


    waitUntilKeyPressed();
    quitSDL(window, renderer, texture);
    return 0;
}
