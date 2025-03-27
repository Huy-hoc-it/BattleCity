#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "game.h"
#include <vector>
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
    SDL_Texture* Menu_name = loadTexture("Menu_name.png", renderer);
    SDL_Texture* You_win = loadTexture("You_win.png", renderer);
    SDL_Texture* You_lose = loadTexture("You_lose.png", renderer);
    SDL_Texture* Start_button = loadTexture("Start_button.png", renderer);
    SDL_Texture* Exit_button = loadTexture("Exit_button.png", renderer);
    texture.push_back(tank_main);
    texture.push_back(tank_enemy);
    texture.push_back(Menu_name);
    texture.push_back(You_win);
    texture.push_back(You_lose);
    texture.push_back(Start_button);
    texture.push_back(Exit_button);

    game(renderer, texture, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);

    waitUntilKeyPressed();
    quitSDL(window, renderer, texture);
    return 0;
}
