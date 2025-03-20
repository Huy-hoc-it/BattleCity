#include <SDL.h>
#include <SDL_image.h>
#include "init_game.h"
#include "drawmap.h"
#include <iostream>
#include <algorithm>

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
    SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255); // Màu xám
    SDL_RenderFillRect(renderer, &bullet_rect);
}

bool Bullet::isInside(int minX, int minY, int maxX, int maxY)
{
    return (x >= minX && y >= minY && x + size_b <= maxX && y + size_b <= maxY);
}

bool Bullet::collision_bullet_wall(vector < vector <int> >& tiles, int tileSize)
{
    int tileX_upon = x / tileSize;
    int tileY_upon = y / tileSize;
    int tileX_bottom = (x + size_b - 1) / tileSize;
    int tileY_bottom = (y + size_b - 1) / tileSize;

    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= tiles.size() || tileY_bottom >= tiles.size()) return false;
    if(tiles[tileX_upon][tileY_upon] >= 1 || tiles[tileX_bottom][tileY_bottom] >= 1 ||
       tiles[tileX_upon][tileY_bottom] >= 1 || tiles[tileX_bottom][tileY_upon] >= 1){

        if(tiles[tileX_upon][tileY_upon] == 1) tiles[tileX_upon][tileY_upon] = 0;
        if(tiles[tileX_bottom][tileY_bottom] == 1) tiles[tileX_bottom][tileY_bottom] = 0;
        if(tiles[tileX_upon][tileY_bottom] == 1) tiles[tileX_upon][tileY_bottom] = 0;
        if(tiles[tileX_bottom][tileY_upon] == 1) tiles[tileX_bottom][tileY_upon] = 0;
        return true; // đụng tường
    }
    return false;
}

void Box::render(SDL_Renderer* renderer,Tilemap& tilemap)
{
    tilemap.loadTileTextures(renderer);
    tilemap.render_map(renderer);
    SDL_Texture* tanktexture = loadTexture("tank_main.png", renderer);
    renderTexture(tanktexture, x, y, sizea, sizea, dir_img, flip, renderer);
}

bool Box::checkCollision(Tilemap& tilemap)
{
    int tileX_upon = x / tilemap.tileSize;
    int tileY_upon = y / tilemap.tileSize;
    int tileX_bottom = (x + sizea - 1) / tilemap.tileSize;
    int tileY_bottom = (y + sizea - 1) / tilemap.tileSize;
    //cout << tileX_upon << " " << tileY_upon << " " << tileX_bottom << " " << tileY_bottom << endl;
    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= tilemap.tiles.size() || tileY_bottom >= tilemap.tiles.size()) return false;
    if(tilemap.tiles[tileX_upon][tileY_upon] > 0 || tilemap.tiles[tileX_bottom][tileY_bottom] > 0 ||
       tilemap.tiles[tileX_upon][tileY_bottom] > 0 || tilemap.tiles[tileX_bottom][tileY_upon] > 0){
        return true; // đụng tường
    }
    return false;
}

void Box::move_left(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(x - 5 >= 0)x -= 5;
    lastDir = LEFT;
    dir_img = 270;
    if(checkCollision(tilemap)){
        x += 5;
        return;
    }
}

void Box::move_right(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(x + sizea + 5 <= SCREEN_WIDTH)x += 5;
    lastDir = RIGHT;
    dir_img = 90;
    if(checkCollision(tilemap)){
        x -= 5;
        return;
    }
}

void Box::move_up(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(y - 5 >= 0)y -= 5;
    lastDir = UP;
    dir_img = 0;
    if(checkCollision(tilemap)){
        y += 5;
        return;
    }
}

void Box::move_down(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    if(y + sizea + 5 <= SCREEN_HEIGHT)y += 5;
    lastDir = DOWN;
    dir_img = 180;
    if(checkCollision(tilemap)){
        y -= 5;
        return;
    }
}

bool Box::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + sizea <= maxX && y + sizea <= maxY);
}

bool Enemy::Collision_Enemy_Wall(Tilemap& tilemap){
    int tileX_upon = x / tilemap.tileSize;
    int tileY_upon = y / tilemap.tileSize;
    int tileX_bottom = (x + size_enemy - 1) / tilemap.tileSize;
    int tileY_bottom = (y + size_enemy - 1) / tilemap.tileSize;
    cout << tileX_upon << " " << tileY_upon << " " << tileX_bottom << " " << tileY_bottom << endl;
    if (tileX_upon < 0 || tileY_upon < 0 || tileX_bottom >= tilemap.tiles.size() || tileY_bottom >= tilemap.tiles.size()) return false;
    if(tilemap.tiles[tileX_upon][tileY_upon] > 0 || tilemap.tiles[tileX_bottom][tileY_bottom] > 0 ||
       tilemap.tiles[tileX_upon][tileY_bottom] > 0 || tilemap.tiles[tileX_bottom][tileY_upon] > 0){
        return true; // đụng tường
    }
    return false;
}

bool Enemy::inside(int minX, int minY, int maxX, int maxY)
{
    return (minX <= x && minY <= y && x + size_enemy <= maxX && y + size_enemy <= maxY);
}

void Enemy::move_enemy(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    x = x + dx;
    y = y + dy;

    if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
        x -= dx;
        y -= dy;

        Direction direc = (Direction)(rand() % 4);
        if(direc == LEFT){
            dx = -speed;
            dy = 0;
            lastDir = LEFT;
            dir_img = 270;
        }
        else if(direc == RIGHT){
            dx = speed;
            dy = 0;
            lastDir = RIGHT;
            dir_img = 90;
        }
        else if(direc == UP){
            dx = 0;
            dy = -speed;
            lastDir = UP;
            dir_img = 0;
        }
        else{
            dx = 0;
            dy = speed;
            lastDir = DOWN;
            dir_img = 180;
        }
    }
}

void Enemy::render_enemy(SDL_Renderer* renderer)
{
    SDL_Texture* tanktexture = loadTexture("enemy_tank.png", renderer);
    renderTexture(tanktexture, x, y, size_enemy, size_enemy, dir_img, flip, renderer);
}

void Enemy::enemy_shoot(vector <Bullet> &bullets_enemy)
{
    bullets_enemy.push_back(Bullet(x + size_enemy / 2 - 10 / 2, y + size_enemy / 2 - 10 / 2, lastDir));
}

void Enemy::move_direc(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    Direction direc = (Direction)(rand() % 4);
    if(direc == LEFT)
    {
        int dx_old = dx;
        int dy_old = dy;
        dx = -speed;
        dy = 0;
        x += dx;
        y += dy;
        if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
            x -= dx;
            y -= dy;
            dx = dx_old;
            dy = dy_old;
            return;
        }
        else{
            x -= dx;
            y -= dy;
        }
        lastDir = LEFT;
        dir_img = 270;
    }
    else if(direc == RIGHT)
    {
        int dx_old = dx;
        int dy_old = dy;
        dx = speed;
        dy = 0;
        x += dx;
        y += dy;
        if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
            x -= dx;
            y -= dy;
            dx = dx_old;
            dy = dy_old;
            return;
        }
        else{
            x -= dx;
            y -= dy;
        }
        lastDir = RIGHT;
        dir_img = 90;
    }
    else if(direc == UP)
    {
        int dx_old = dx;
        int dy_old = dy;
        dx = 0;
        dy = -speed;
        x += dx;
        y += dy;
        if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
            x -= dx;
            y -= dy;
            dx = dx_old;
            dy = dy_old;
            return;
        }
        else{
            x -= dx;
            y -= dy;
        }
        lastDir = UP;
        dir_img = 0;
    }
    else
    {
        int dx_old = dx;
        int dy_old = dy;
        dx = 0;
        dy = speed;
        x += dx;
        y += dy;
        if(Collision_Enemy_Wall(tilemap) || !inside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)){
            x -= dx;
            y -= dy;
            dx = dx_old;
            dy = dy_old;
            return;
        }
        else{
            x -= dx;
            y -= dy;
        }
        lastDir = DOWN;
        dir_img = 180;
    }
}

