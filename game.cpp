#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "init_game.h"

using namespace std;

void game(SDL_Renderer* renderer, SDL_Texture* texture, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    SDL_Event e;
    Box box;
    box.x = 0;
    box.y = 0;

    vector <Bullet> bullets;

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
                    box.move_left(SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_RIGHT:
                    box.move_right(SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_UP:
                    box.move_up(SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_DOWN:
                    box.move_down(SCREEN_WIDTH, SCREEN_HEIGHT);
                    break;
                case SDLK_SPACE:
                    bullets.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2, box.y + box.sizea / 2 - 10 / 2, box.lastDir));
                default:
                    break;
                }
            }
        }
        for (size_t i = 0; i < bullets.size(); )
        {
            bullets[i].move();
            if (bullets[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT))
            {
                bullets[i].render(renderer);
                ++i;
            }
            else
            {
                bullets.erase(bullets.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình
            }
        }

        box.render(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
