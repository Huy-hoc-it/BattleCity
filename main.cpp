#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "game.h"
#include <vector>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Battle city";
const int enemyCount = 3;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    TTF_Font* font = loadFont("times.ttf", 28);

    vector <SDL_Texture*> texture;
    SDL_Texture* tank_main = loadTexture("tank_main.png", renderer);
    SDL_Texture* tank_enemy = loadTexture("enemy_tank.png", renderer);
    SDL_Texture* Menu_name = loadTexture("Menu_name.png", renderer);
    SDL_Texture* You_win = loadTexture("You_win.png", renderer);
    SDL_Texture* You_lose = loadTexture("You_lose.png", renderer);
    SDL_Texture* Start_button = loadTexture("Start_button.png", renderer);
    SDL_Texture* Exit_button = loadTexture("Exit_button.png", renderer);
    SDL_Texture* Try_again = loadTexture("Try_again.png", renderer);
    SDL_Texture* Pause_button = loadTexture("Pause_button.png", renderer);
    texture.push_back(tank_main);
    texture.push_back(tank_enemy);
    texture.push_back(Menu_name);
    texture.push_back(You_win);
    texture.push_back(You_lose);
    texture.push_back(Start_button);
    texture.push_back(Exit_button);
    texture.push_back(Try_again);
    texture.push_back(Pause_button);

    vector <SDL_Texture*> explosionTextures;
    SDL_Texture* explosion1 = loadTexture("explosion1.png", renderer);
    SDL_Texture* explosion2 = loadTexture("explosion2.png", renderer);
    SDL_Texture* explosion3 = loadTexture("explosion3.png", renderer);
    explosionTextures.push_back(explosion1);
    explosionTextures.push_back(explosion2);
    explosionTextures.push_back(explosion3);

    game(renderer, font, texture, explosionTextures, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);

    //waitUntilKeyPressed();
    quitSDL(window, renderer, texture, explosionTextures, font);
    return 0;
}
