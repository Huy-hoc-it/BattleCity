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

    vector <Bullet> bullets;
    Tilemap tilemap;
    tilemap.loadFromFile("map_1.txt");
    bool running = true;
    while(running)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

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
                    bullets.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2, box.y + box.sizea / 2 - 10 / 2, box.lastDir));
                default:
                    break;
                }
            }
        }
        for (size_t i = 0; i < bullets.size(); ) // size_t: kieu du lieu unsigned, khong am
        {
            bullets[i].move();
            if (!bullets[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT) || bullets[i].collision_bullet_wall(tilemap.tiles, tilemap.tileSize))
            {
                bullets.erase(bullets.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình hoặc chạm vào tường gạch
            }
            else
            {
                bullets[i].render(renderer);
                ++i;
            }
        }

        box.render(renderer, tilemap);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
