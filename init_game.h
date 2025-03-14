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

    void render(SDL_Renderer* renderer);

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    bool inside(int minX, int minY, int maxX, int maxY);
};
