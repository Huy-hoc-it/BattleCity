#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "init_game.h"
#include "drawmap.h"
#include <algorithm>
#include "menu.h"
#include "animation.h"
#include "User_interface.h"

using namespace std;

void game(SDL_Renderer* renderer, TTF_Font* font, vector <SDL_Texture*>& texture, vector <SDL_Texture*>& explosionTextures,
          const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount);

void remake(Box& box, Tilemap& tilemap, vector <Enemy>& enemies, bool& active,int& shoot_timer,
             int& enemy_direc_timer, bool& victory, bool& defeat, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount);

#endif // GAME_H

