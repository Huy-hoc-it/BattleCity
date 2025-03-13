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


void Box::render(SDL_Renderer* renderer, SDL_Texture* texture)
{
    tilemap.loadFromFile("map_1.txt");
    tilemap.render_map(renderer, texture);
    texture = loadTexture("tank_main.png", renderer);
    renderTexture(texture, x, y, sizea, sizea, dir_img, flip, renderer);
}

void Box::move_left()
{
    x -= 5;
    lastDir = LEFT;
    dir_img = 270;
}

void Box::move_right()
{
    x += 5;
    lastDir = RIGHT;
    dir_img = 90;
}

void Box::move_up()
{
    y -= 5;
    lastDir = UP;
    dir_img = 0;
}

void Box::move_down()
{
    y += 5;
    lastDir = DOWN;
    dir_img = 180;
}

bool Box::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + sizea <= maxX && y + sizea <= maxY);
}


