#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "game.h"
#include <vector>
#include <map>
#include <string>
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

    map<string, SDL_Texture*> texture;
    texture["tank_main"] = loadTexture("image/tank_main.png", renderer);
    texture["tank_enemy"] = loadTexture("image/enemy_tank.png", renderer);
    texture["Menu_name"] = loadTexture("image/Menu_name.png", renderer);
    texture["You_win"] = loadTexture("image/You_win.png", renderer);
    texture["You_lose"] = loadTexture("image/You_lose.png", renderer);
    texture["Start_button"] = loadTexture("image/Start_button.png", renderer);
    texture["Exit_button"] = loadTexture("image/Exit_button.png", renderer);
    texture["Try_again"] = loadTexture("image/Try_again.png", renderer);
    texture["Pause_button"] = loadTexture("image/Pause_button.png", renderer);
    texture["Play_button"] = loadTexture("image/Play_button.png", renderer);

    vector <SDL_Texture*> explosionTextures;
    SDL_Texture* explosion1 = loadTexture("image/explosion1.png", renderer);
    SDL_Texture* explosion2 = loadTexture("image/explosion2.png", renderer);
    SDL_Texture* explosion3 = loadTexture("image/explosion3.png", renderer);
    explosionTextures.push_back(explosion1);
    explosionTextures.push_back(explosion2);
    explosionTextures.push_back(explosion3);

    game(renderer, font, texture, explosionTextures, SCREEN_WIDTH, SCREEN_HEIGHT, enemyCount);

    //waitUntilKeyPressed();
    quitSDL(window, renderer, texture, explosionTextures, font);
    return 0;
}
