#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "drawmap.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void Tilemap::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "file can't open: " << filename << endl;
        return;
    }

    tiles.clear();
    string line;
    while (getline(file, line))
    {
        vector<int> row;
        for(int i = 0; i < int(line.size()); i++)
        {
            if(line[i] != ',' && line[i] != ' ')
            {
                row.push_back(int(line[i] - '0'));
            }
        }
        tiles.push_back(row);
        width_map = max(width_map, (int)row.size());
    }
    height_map = tiles.size();
    file.close();
}

void Tilemap::render_map(SDL_Renderer* renderer, SDL_Texture* texture)
{
    for(int i = 0; i < height_map; i++)
    {
        for(int j = 0; j < width_map; j++)
        {
            if(tiles[i][j] != 0)
            {
                SDL_Rect rect_map = {i*tileSize, j*tileSize, tileSize, tileSize};
                string tile;
                tile = to_string(tiles[i][j]);
                tile += ".png";
                texture = loadTexture(tile.c_str(), renderer);
                SDL_RenderCopy(renderer, texture, NULL, &rect_map);
            }
        }
    }
}
