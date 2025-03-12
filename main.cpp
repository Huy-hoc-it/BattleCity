#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "SDL_utils.h"
#include "init_game.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const char* WINDOW_TITLE = "Battle city";


int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

    SDL_Event e;
    Box box;
    box.x = 10;
    box.y = 10;

    vector <Bullet> bullets;

    bool running = true;

    while(running){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT) running = false;
            if(e.type == SDL_KEYDOWN){
                switch (e.key.keysym.sym){
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_LEFT:
                        box.move_left();
                        break;
                    case SDLK_RIGHT:
                        box.move_right();
                        break;
                    case SDLK_UP:
                        box.move_up();
                        break;
                    case SDLK_DOWN:
                        box.move_down();
                        break;
                    case SDLK_SPACE:
                        bullets.push_back(Bullet(box.x + box.sizea / 2 - 10 / 2, box.y + box.sizea / 2 - 10 / 2, box.lastDir));
                    default:
                        break;
                }
            }
        }
        for (size_t i = 0; i < bullets.size(); ) {
            bullets[i].move();
            if (bullets[i].isInside(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)) {
                bullets[i].render(renderer);
                ++i;
            } else {
                bullets.erase(bullets.begin() + i); // Xóa viên đạn nếu ra ngoài màn hình
            }
        }

        box.render(renderer, texture);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    waitUntilKeyPressed();
    quitSDL(window, renderer, texture);
    return 0;
}
