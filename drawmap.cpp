#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "drawmap.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void Tilemap::loadTileTextures(SDL_Renderer* renderer)
{
    for(int i = 1; i <= numTile; i++){
        string fileName = to_string(i) + ".png";
        tileTextures[i] = loadTexture(fileName.c_str(), renderer);
    }
}

void Tilemap::loadFromFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "file can't open: " << filename << endl;
        return;
    }
    else{
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
}

void Tilemap::render_map(SDL_Renderer* renderer)
{
    for(int i = 0; i < height_map; i++)
    {
        for(int j = 0; j < width_map; j++)
        {
            int tileID = tiles[i][j];
            if(tileID != 0 && tileTextures.count(tileID))
            {
                renderTexture(tileTextures[tileID], i*tileSize, j*tileSize, tileSize, tileSize, 0, SDL_FLIP_NONE, renderer);
            }
        }
    }
}
