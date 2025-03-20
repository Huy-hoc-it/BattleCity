#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "init_game.h"
#include "drawmap.h"

using namespace std;

void game(SDL_Renderer* renderer, SDL_Texture* texture, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    SDL_Event e;
    Box box;
    box.x = 0;
    box.y = 0;

    vector <Bullet> bullets_main;
    vector <Bullet> bullets_enemy;
    Tilemap tilemap;
    tilemap.loadFromFile("map_1.txt");
    bool running = true;

    Enemy enemy(SCREEN_WIDTH - 30, 0);

    int shoot_timer = 0;
    while(running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        shoot_timer++;

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
                bullets_main[i].render(renderer);
                ++i;
            }
        }

        enemy.move_enemy(tilemap, SCREEN_WIDTH, SCREEN_HEIGHT);

        if(shoot_timer > 60){
            enemy.enemy_shoot(bullets_enemy);
            shoot_timer = 0;
        }

        for (size_t i = 0; i < bullets_enemy.size(); ) // size_t: kieu du lieu unsigned, khong am
        {
            bullets_enemy[i].move();
            if (!bullets_enemy[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) || bullets_enemy[i].collision_bullet_wall(tilemap.tiles, tilemap.tileSize))
            {
                bullets_enemy.erase(bullets_enemy.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình hoặc chạm vào tường gạch
            }
            else
            {
                bullets_enemy[i].render(renderer);
                ++i;
            }
        }

        box.render(renderer, tilemap);
        enemy.render_enemy(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
