#include <SDL.h>
#include <SDL_image.h>
#include "init_game.h"
#include "drawmap.h"
using namespace std;
const int BULLET_SPEED = 8;

enum Direction;

void Bullet::move()
{
    switch (dir)
    {
    case LEFT:
        x -= BULLET_SPEED;
        break;
    case RIGHT:
        x += BULLET_SPEED;
        break;
    case UP:
        y -= BULLET_SPEED;
        break;
    case DOWN:
        y += BULLET_SPEED;
        break;
    }
}

void Bullet::render(SDL_Renderer* renderer)
{
    SDL_Rect bullet_rect = { x, y, size_b, size_b };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
    SDL_RenderFillRect(renderer, &bullet_rect);
}

bool Bullet::isInside(int minX, int minY, int maxX, int maxY)
{
    return (x >= minX && y >= minY && x + size_b <= maxX && y + size_b <= maxY);
}


void Box::render(SDL_Renderer* renderer)
{
    tilemap.loadFromFile("map_1.txt");
    SDL_Texture* tiletexture = loadTexture("1.png", renderer);
    tilemap.render_map(renderer, tiletexture);
    SDL_Texture* tanktexture = loadTexture("tank_main.png", renderer);
    renderTexture(tanktexture, x, y, sizea, sizea, dir_img, flip, renderer);
}

bool Box::checkCollision(vector <vector<int>> & tiles, int tileSize)
{
    int tileX_upon = x / tileSize;
    int tileY_upon = y / tileSize;
    int tileX_bottom = (x + sizea - 1) / tileSize;
    int tileY_bottom = (y + sizea - 1) / tileSize;
    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= tiles.size() || tileY_bottom >= tiles.size()) return false;
    if(tiles[tileY_upon][tileX_upon] > 0 || tiles[tileY_bottom][tileX_bottom] > 0 ||
       tiles[tileY_upon][tileX_bottom] > 0 || tiles[tileY_bottom][tileX_upon] > 0){
        return true; // đụng tường
    }
    return false;
}

void Box::move_left(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(x - 5 >= 0)x -= 5;
    lastDir = LEFT;
    dir_img = 270;
    if(checkCollision(tilemap.tiles, tilemap.tileSize)){
        x += 5;
        return;
    }
}

void Box::move_right(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(x + sizea + 5 <= SCREEN_WIDTH)x += 5;
    lastDir = RIGHT;
    dir_img = 90;
    if(checkCollision(tilemap.tiles, tilemap.tileSize)){
        x -= 5;
        return;
    }
}

void Box::move_up(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(y - 5 >= 0)y -= 5;
    lastDir = UP;
    dir_img = 0;
    if(checkCollision(tilemap.tiles, tilemap.tileSize)){
        y += 5;
        return;
    }
}

void Box::move_down(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(y + sizea + 5 <= SCREEN_HEIGHT)y += 5;
    lastDir = DOWN;
    dir_img = 180;
    if(checkCollision(tilemap.tiles, tilemap.tileSize)){
        y -= 5;
        return;
    }
}

bool Box::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + sizea <= maxX && y + sizea <= maxY);
}


