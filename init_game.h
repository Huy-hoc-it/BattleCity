#ifndef INITGAME_H
#define INITGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include "drawmap.h"
using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN };

struct Bullet{
    int x, y;
    int size_b = 10;
    Direction dir;
    SDL_Renderer* renderer;
    Bullet (int startX, int startY, Direction direction){
        x = startX;
        y = startY;
        dir = direction;
    }
    void move();

    void render(SDL_Renderer* renderer);

    bool isInside(int minX, int minY, int maxX, int maxY);

    bool collision_bullet_wall(vector < vector <int> >& tiles, int tileSize);
};

struct Box{
    int x;
    int y;
    int sizea = 30;
    double dir_img = 90;
    Tilemap tilemap;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Direction lastDir = RIGHT;
    SDL_Texture* texture = nullptr;
    SDL_Renderer* renderer;

    void render(SDL_Renderer* renderer, Tilemap& tilemap);

    void move_left(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_right(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_up(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_down(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

    bool checkCollision(Tilemap& tilemap);
    bool inside(int minX, int minY, int maxX, int maxY);
};

struct Enemy{
    int x, y;
    int dx, dy;
    int speed;
    int size_enemy = 30;
    double dir_img = 270;
    Tilemap tilemap;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Direction lastDir = LEFT;

    Enemy(int startX, int startY) {
        x = startX;
        y = startY;
        speed = 2;
        dx = -speed;
        dy = 0;
    }

    void move_enemy(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void render_enemy(SDL_Renderer* renderer);
    void enemy_shoot(vector <Bullet> &bullets_enemy);
    void move_direc(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

    bool Collision_Enemy_Wall(Tilemap& tilemap);
    bool inside(int minX, int minY, int maxX, int maxY);
};

#endif // INITGAME_H
