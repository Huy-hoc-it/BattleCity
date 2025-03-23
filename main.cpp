#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "game.h"
#include <vector>
#include <SDL_ttf.h>
using namespace std;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Battle city";
const int enemyCount = 3;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);


    vector <SDL_Texture*> texture;
    SDL_Texture* tank_main = loadTexture("tank_main.png", renderer);
    SDL_Texture* tank_enemy = loadTexture("enemy_tank.png", renderer);
    texture.push_back(tank_main);
    texture.push_back(tank_enemy);

    game(renderer, texture, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);

    waitUntilKeyPressed();
    quitSDL(window, renderer, texture);
    return 0;
}
