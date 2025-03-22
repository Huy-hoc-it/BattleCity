#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "init_game.h"
#include "drawmap.h"
#include <algorithm>
using namespace std;

void game(SDL_Renderer* renderer, vector <SDL_Texture*>& texture, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const int enemyCount)
{
    srand(time(nullptr));
    SDL_Event e;
    Box box;
    box.x = 0;
    box.y = 0;

    vector <Bullet> bullets_main;
    Tilemap tilemap;
    tilemap.loadFromFile("map_1.txt");
    bool running = true;

    vector <Enemy> enemies;

    spawnEnemies(enemies, enemyCount, tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);

    int shoot_timer = 0;
    int enemy_direc_timer = 0;
    while(running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        shoot_timer++;
        enemy_direc_timer++;

        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT) running = false;
            if(e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LEFT:
                    box.move_left(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_RIGHT:
                    box.move_right(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_UP:
                    box.move_up(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_DOWN:
                    box.move_down(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_SPACE:
                    bullets_main.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2, box.y + box.sizea / 2 - 10 / 2, box.lastDir));
                default:
                    break;
                }
            }
        }
        for (size_t i = 0; i < bullets_main.size(); ) // size_t: kieu du lieu unsigned, khong am
        {
            bullets_main[i].move();
            if (!bullets_main[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) || bullets_main[i].collision_bullet_wall(tilemap.tiles, tilemap.tileSize))
            {
                bullets_main.erase(bullets_main.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình hoặc chạm vào tường gạch
            }
            else
            {
                for(int j = 0; j < enemyCount; j++){
                    if(bullets_main[i].collision_bullet_tank_enemy(enemies[j])){
                        enemies[j].alive = false;
                        bullets_main.erase(bullets_main.begin() + i);
                    }
                }
                bullets_main[i].render(renderer);
                ++i;
            }
        }
        for(int i = 0; i < enemyCount; i++){
            enemies[i].move_enemy(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        if(shoot_timer > 60){
            for(int i = 0; i < enemyCount; i++){
                enemies[i].enemy_shoot();
            }
            shoot_timer = 0;
        }
        if(enemy_direc_timer > 180){
            for(int i = 0; i < enemyCount; i++){
                enemies[i].move_direc(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
            }
            enemy_direc_timer = 0;
        }
        for(int i = 0; i < enemyCount; i++){
            enemies[i].update_bullets(renderer, box, tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);
        }

        tilemap.loadTileTextures(renderer);
        tilemap.render_map(renderer);
        box.render(renderer, texture[0]);
        for(int i = 0; i < enemyCount; i++){
            enemies[i].render_enemy(renderer, texture[1]);
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
