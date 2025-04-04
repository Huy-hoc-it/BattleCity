#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "menu.h"

using namespace std;

struct UI
{
    SDL_Renderer* renderer;
    TTF_Font* font;
    Button pauseButton;

    UI(SDL_Renderer* ren, TTF_Font* font_, SDL_Texture* pauseTexture);

    void renderText(const string& text, int x, int y, int w, int h);
    void render(int& score);
};

#endif // UI_H
