#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL.h>
#include <vector>
#include <iostream>

using namespace std;

struct Explosion {
    int x, y;
    int currentFrame;           // khung hình hiện tại
    int totalFrames;
    int frameDelay;             // số frame chờ giữa mỗi khung hình
    int delayCounter;           // biến đếm thời gian giữa các frame
    bool active;
    vector<SDL_Texture*> textures;

    Explosion(int x_, int y_, vector<SDL_Texture*>& explosionTextures);
    void update();
    void render(SDL_Renderer* renderer);
};

struct ExplosionManager { //quản lí vụ nổ
    vector<Explosion> explosions;

    void addExplosion(int x, int y, vector<SDL_Texture*>& explosionTextures);
    void updateExplosions();
    void renderExplosions(SDL_Renderer* renderer);
};

#endif
