#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Tilemap{
    vector <vector<int>> tiles;
    int width_map = 0;
    int height_map = 0;
    int tileSize = 30;

    void loadFromFile(const string& filename);

    void render_map(SDL_Renderer* renderer, SDL_Texture* texture);
};

#endif
