#ifndef DRAWMAP_H
#define DRAWMAP_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

struct Tilemap{
    vector <vector<int>> tiles;
    int width_map = 0;
    int height_map = 0;
    int tileSize = 30;
    int numTile = 3;
    map<int, SDL_Texture*> tileTextures;

    void loadTileTextures(SDL_Renderer* renderer);

    void loadFromFile(const string& filename);

    void render_map(SDL_Renderer* renderer);
};

#endif
