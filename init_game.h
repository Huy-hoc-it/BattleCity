#ifndef INITGAME_H
#define INITGAME_H

#include <SDL.h>
#include <SDL_image.h>
#include "drawmap.h"
#include <iostream>
#include <algorithm>
#include "animation.h"
#include "media.h"

using namespace std;

enum Direction { LEFT, RIGHT, UP, DOWN };

struct Box;
struct Enemy;

struct Bullet{
    int x, y;
    int size_b = 10;
    Direction dir;
    SDL_Renderer* renderer;
    int Bullet_speed;
    Bullet (int startX, int startY, int Bullet_speed_, Direction direction){
        x = startX;
        y = startY;
        Bullet_speed = Bullet_speed_;
        dir = direction;
    }
    void move();

    void render(SDL_Renderer* renderer);

    bool isInside(int minX, int minY, int maxX, int maxY);

    bool collision_bullet_wall(vector < vector <int> >& tiles, int tileSize);

    bool collision_bullet_tank_enemy(Enemy& enemy);
    bool collision_bullet_tank_main(Box& box);
};

struct Box{
    int x;
    int y;
    int sizea = 30;
    double dir_img = 90;
    Tilemap tilemap;
    int speed;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    Direction lastDir = RIGHT;
    SDL_Renderer* renderer;
    vector <Bullet> bullets_main;
    bool alive = true;

    Box(int startX, int startY, int speed_){
        x = startX;
        y = startY;
        speed = speed_;
    }

    void render(SDL_Renderer* renderer, SDL_Texture* texture);

    void move_left(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_right(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_up(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_down(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void main_shoot(SDL_Renderer* renderer,vector<Enemy>& enemies, Tilemap& tilemap, ExplosionManager& explosionManager,
                    vector <SDL_Texture*>& explosionTextures, SoundManager& soundManager, int enemyCount, int& enemy_alive,
                    bool& victory, int& score, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

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
    vector <Bullet> bullets_enemy;
    bool alive = true;

    Enemy(int startX, int startY, int speed_) {
        x = startX;
        y = startY;
        speed = speed_;
        dx = -speed;
        dy = 0;
    }

    void move_enemy(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void render_enemy(SDL_Renderer* renderer, SDL_Texture* texture);
    void enemy_shoot(const int BULLET_SPEED);
    void update_bullets(SDL_Renderer* renderer,Box& box, Tilemap& tilemap, ExplosionManager& explosionManager,
                     vector <SDL_Texture*>& explosionTextures, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
    void move_direc(Tilemap& tilemap, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

    bool Collision_Enemy_Wall(Tilemap& tilemap);
    bool inside(int minX, int minY, int maxX, int maxY);
};

void getRandomPosition(Tilemap& tilemap, int& x, int& y, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
void spawnEnemies(vector <Enemy>& enemies, int enemyCount, Tilemap tilemap, const int Tank_speed, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

#endif // INITGAME_H
