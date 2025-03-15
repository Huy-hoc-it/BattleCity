#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "init_game.h"

using namespace std;

void game(SDL_Renderer* renderer, SDL_Texture* texture, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

#endif // GAME_H

