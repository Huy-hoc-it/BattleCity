#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include "SDL_utils.h"
#include <string>

using namespace std;

struct Button
{
    SDL_Rect rect;
    string text;
    SDL_Texture* texture;

    Button(const string& t, int x, int y, int w, int h, SDL_Texture* _texture){
        text = t;
        texture = _texture;
        rect = {x, y, w, h};
    }
    bool isMouseOver(int mouseX, int mouseY);

    void render(SDL_Renderer* renderer);
};

struct Menu
{
    SDL_Renderer* renderer;
    SDL_Texture* titleTexture;
    SDL_Rect titleRect;
    vector<Button> buttons;

    Menu(SDL_Renderer* ren, SDL_Texture* _titleTexture, int x, int y, int w, int h){
        renderer = ren;
        titleTexture = _titleTexture;
        titleRect = {x, y, w, h};
    }
    void render();
    string handleMouseEvent(int mouseX, int mouseY);
};


#endif
